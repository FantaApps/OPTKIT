/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   07/24/16 - Add context switching support 
 *  stplaydog   04/24/16 - Add logger support 
 *  stplaydog   04/16/16 - Fixed some minor bugs 
 *  stplaydog   04/12/16 - Usng main, we can collect all basic graph info now.
 *  stplaydog   03/05/16 - Use the new parser 
 *  stplaydog   12/13/15 - Fixed bugs related to print_help() 
 *  stplaydog   08/02/15 - Fixed bugs to make it compile.
 *  stplaydog   08/01/15 - Creation
 *
**/

#include "list.h"
#include "node.h"
#include "csr.h"
#include "truss.h"
#include "Stats.h"
#include "Config.h"
#include "bgl.h"
#include "core.h"
#include "dbscan.h"
#include "CrimeSTModel.h"
#include "../libs/RTree.h"
#include "../libs/Parser.h"
#include <getopt.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

void set_logger();
void define_arguments(Parser &parser);
void parse_arguments(Parser &parser);
void process();
void process_with_context(const string &infile, const string &oufile);
void process_without_context(const string &infile, const string &oufile);

BoolOption        truss         ('t', "truss",      false, "truss apllication");
BoolOption        stmodel       ('s', "stmodel",    false, "stmodel application");
BoolOption        resume        ('r', "resume",     false, "resume from a previous run");
BoolOption        bgl           ('b', "bgl",        false, "enable BGL or not");
StringOption      logger        ('l', "logger",     false, "log file name");
StringOption      input         ('i', "input",      true , "input file name");
StringOption      output        ('o', "output",     true , "output file name");
StringListOption  coord         ('c', "coord",      false, "spatial temporal coordinates");



/**
 * Main function of OPTKIT
**/
int32_t main(int32_t argc , const char *argv[])
{
    Parser parser;
    define_arguments(parser);
    vector<string> otherArguments = parser.parse(argc, (char**)argv);

    set_logger();

    parse_arguments(parser);
    process();

    LOG(INFO) << "Finishing OPTKIT...";
    return 0;
}

/**
 * @brief   Set up google log, it does following things:
 *          1) determine the logging folder, which is in OPTKIT/log;
 *          2) If folder does not exist, create one;
 *          3) If log file name is specified, use this name, else just use folder.
 *
 * @return N/A
**/
void set_logger()
{
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        ERROR_PRINT();
    }
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    char *optkitPath = strstr(cCurrentPath, "OPTKIT") + 6;
    *optkitPath = '\0';
    string log_dir = cCurrentPath;
    log_dir += "/log/";

    if(!Utils::check_create_dir(log_dir.c_str()))
    {
        string mkdir_expr = "mkdir -p ";
        mkdir_expr       += log_dir;
        const int dir_err = system(mkdir_expr.c_str());
        if (-1 == dir_err)
        {
            printf("Error creating directory!n");
            ERROR_PRINT();
        }
    }

    if(logger.isSet())
    {
        log_dir += logger.getValue(); 
        google::SetLogDestination(google::INFO, log_dir.c_str());
    }
    else
    {
        FLAGS_log_dir = log_dir.c_str();
    }

    google::InitGoogleLogging("optkit");
    LOG(INFO) << "Initiating OPTKIT...";
}

/**
 * @brief       This function is used to load parameters
 *
 * @param[in/out]       parser      This is the parameter parser
 **/
void define_arguments(Parser &parser)
{
    parser.addOption(truss)
        .addOption(stmodel)
        .addOption(bgl)
        .addOption(input)
        .addOption(output)
        .addOption(logger)
        .addOption(coord);
}

void parse_arguments(Parser &parser)
{
    LOG(INFO) << "Parse arguments...";

    string key, val;

    if(truss.isSet())
    {
        key = "application";
        val = "truss";
        Config::instance()->set(key, val);
        LOG(INFO) << "Application is truss decomposition...";
    }
    else if(stmodel.isSet())
    {
        key = "application";
        val = "stmodel";
        Config::instance()->set(key, val);
        LOG(INFO) << "Application is Spatial Temporal Crime Model...";
    }

    key = "infile";
    val = input.getValue();
    Config::instance()->set(key, val);
    LOG(INFO) << "Infile: "<<val;

    key = "outfile";
    val = output.getValue();
    val += ".json";
    Config::instance()->set(key, val);
    LOG(INFO) << "Outfile: "<<val;

    key = "coord";
    val = "";
    list<string> values = coord.getValue();
    vector<int> v;
    for(auto it = values.begin(); it != values.end(); ++it)
        v.push_back(stoi(*it));
    Utils::vec_to_string<int>(v, val);
    Config::instance()->set(key, val);
    LOG(INFO) << "Coord: "<<val;

}

/**
 * @brief       process input parameters and perform according functions
 *
 * @param[in/out]       parser      This is the parameter parser
**/
void process()
{
    string infile = input.getValue();
    string oufile = output.getValue();

    if(truss.isSet())
    {
        CSR g(infile.c_str());
        Truss t(g.get_num_e(), g.get_num_c());
        t.truss_decomosition(g, oufile.c_str(), 5);
    }
    else if(stmodel.isSet())
    {
        if(coord.isSet())
        {
            if(resume.isSet())
            {
                process_with_context(infile, oufile);
            }
            else
            {
                process_without_context(infile, oufile);
            }
        }
        else
        {
            LOG(ERROR)<<"Coordinates are not specified!";
            fprintf(stderr, "You should specify coordiates!\n");
            ERROR_PRINT();
        }
    }
}

void process_with_context(const string &infile, const string &oufile)
{
    Utils::deserialize_obj<Config>(*Config::instance(), 
            string("../run/config/config.conf"));
    // Initialize Spatial Temporal model
    CrimeSTModel stm;
    if(Config::instance()->get("stm") == "set")
    {
        LOG(INFO) << "Reloading Crime Spatial Temporal model...";
        Utils::deserialize_obj<CrimeSTModel>(stm, 
                string("../run/config/stmodel.conf"));
    }
    else
    {
        LOG(INFO) << "Initializing Crime Spatial Temporal model...";
        stm = CrimeSTModel(infile.c_str());
    }

    Utils::serialize_obj<CrimeSTModel>(stm, "../run/config/stmodel.conf");
    Config::instance()->set(string("stm"), "set");
    Utils::serialize_obj<Config>(*Config::instance(), "../run/config/config.conf");

    // Build Edge Lists based on connected component
    string coord_val = Config::instance()->get("coord");
    vector<string> _coord = Utils::split(coord_val, ',');

    edge_list_CC el_cc;
    if(Config::instance()->get("el_cc") == "set")
    {
        LOG(INFO) << "Reloading edge list by CC...";
        Utils::deserialize_obj<edge_list_CC>(el_cc, 
                string("../run/config/el_cc.conf"));
    }
    else
    {
        LOG(INFO) << "Start getting edge list by CC...";
        el_cc = stm.build_edge_list_CC(stoi(_coord[0]),
                stoi(_coord[1]),
                stoi(_coord[2]));
    }

    Utils::serialize_obj<edge_list_CC>(el_cc, "../run/config/el_cc.conf");
    Config::instance()->set(string("el_cc"), "set");
    Utils::serialize_obj<Config>(*Config::instance(), "../run/config/config.conf");


    // Process each connected component compute their graph properties
    LOG(INFO) << "There are "<<el_cc.size()<<" number of CCs in total, start processing...";

    string range = _coord[0] + "," + _coord[1] + "," + _coord[2];
    Stats::instance()->write_content(Stats::RANGE, range); 
    string girth_val = "1000";
    Stats::instance()->write_content(Stats::GIRTH, girth_val); 
    Stats::instance()->write_content(Stats::DATANAME, const_cast<string&>(infile)); 

    int iter = 0;
    if(resume.isSet() && 
            Config::instance()->get("iteration") != "NOT_FOUND")
    {
        iter = stoi(Config::instance()->get("iteration"));
    }

    for(auto it = el_cc.begin()+iter; it != el_cc.end(); ++it)
    {
        int i = it-el_cc.begin();
        LOG(INFO)<<"Computing the "<<i<<"th CC...";
        // compute truss
        LOG(INFO) << "Building CSR based on edges...";
        CSR g1(*it);

        LOG(INFO) << "Start initializing truss...";
        Truss t(g1.get_num_e(), g1.get_num_c());

        LOG(INFO) << "Start performing truss decomposition...";
        string CC_truss_out = oufile + "_" + to_string(i) + ".txt";
        t.truss_decomosition(g1, CC_truss_out.c_str(), 5);

        LOG(INFO) << "Start performing graph computations...";
        BGL g(*it);
        g.compute_all();
        Utils::serialize_obj<Stats>(*Stats::instance(),   "../run/config/stats.conf");
        Config::instance()->set(string("iteration"), to_string(i));
        Utils::serialize_obj<Config>(*Config::instance(), "../run/config/config.conf");
    }

    LOG(INFO)<<"Writing results to JSON file...";
    Stats::instance()->serialize();
}

void process_without_context(const string & infile, const string &oufile)
{
    LOG(INFO) << "Initializing Crime Spatial Temporal model...";
    CrimeSTModel stm(infile.c_str());

    string coord_val = Config::instance()->get("coord");
    vector<string> _coord = Utils::split(coord_val, ',');

    LOG(INFO) << "Start getting edge list by CC...";
    // compute bgl related info
    edge_list_CC el_cc = stm.build_edge_list_CC(stoi(_coord[0]),
            stoi(_coord[1]),
            stoi(_coord[2]));

    LOG(INFO) << "There are "<<el_cc.size()<<" number of CCs in total, start processing...";

    int i=0;
    for(auto it = el_cc.begin(); it != el_cc.end(); ++it, i++)
    {
        LOG(INFO)<<"Computing the "<<i<<"th CC...";
        // compute truss
        LOG(INFO) << "Building CSR based on edges...";
        CSR g1(*it);

        LOG(INFO) << "Start initializing truss...";
        Truss t(g1.get_num_e(), g1.get_num_c());

        LOG(INFO) << "Start performing truss decomposition...";
        Config::instance()->set("comp", "ktruss");
        string CC_truss_out = oufile + "_" + to_string(i) + ".txt";
        t.truss_decomosition(g1, CC_truss_out.c_str(), 5);

        LOG(INFO) << "Start performing core decomposition...";
        Config::instance()->set("comp", "kcore");
        Core *core = new Core(g1.get_num_e(), g1.get_num_c());
        string CC_core_out = oufile + "_" + to_string(i) + "_core.txt";
        core->k_core(g1, CC_core_out.c_str(), 5);

        LOG(INFO) << "Start performing dbscan decomposition...";
        Config::instance()->set("comp", "dbscan");
        Core *dbscan = new DBSCAN(g1.get_num_e(), g1.get_num_c());
        string CC_dbscan_out = oufile + "_" + to_string(i) + "_dbscan.txt";
        dbscan->k_core(g1, CC_dbscan_out.c_str(), 5);

        LOG(INFO) << "Start performing graph computations...";
        if(bgl.isSet())
        {
            BGL g(*it);
            g.compute_all();
        }
        else
        {
            BGL g(*it);
            g.compute_core();
        }
    }

    LOG(INFO)<<"Writing results to JSON file...";
    string range = _coord[0] + "," + _coord[1] + "," + _coord[2];
    Stats::instance()->write_content(Stats::RANGE, range); 
    string girth_val = "1000";
    Stats::instance()->write_content(Stats::GIRTH, girth_val); 
    Stats::instance()->write_content(Stats::DATANAME, const_cast<string&>(infile)); 
    Stats::instance()->serialize();
}
