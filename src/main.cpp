/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
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
#include "../libs/RTree.h"
#include "csr.h"
#include "truss.h"
#include "CrimeSTModel.h"
#include "Stats.h"
#include "Config.h"
#include "bgl.h"
#include <getopt.h>
#include "../libs/Parser.h"

void define_arguments(Parser &parser);
void parse_arguments(Parser &parser, int argc, const char* argv[]);
void process(Parser &parser);

BoolOption        truss         ('t', "truss",      false, "truss apllication");
BoolOption        stmodel       ('s', "stmodel",    false, "stmodel application");
StringOption      input         ('i', "input",      true , "input file name");
StringOption      output        ('o', "output",     true , "output file name");
StringListOption  coord         ('c', "coord",      false, "spatial temporal coordinates");



/**
 * Main function of OPTKIT
**/
int32_t main(int32_t argc , const char *argv[])
{
    google::InitGoogleLogging("optkit");
    LOG(INFO) << "Initiating OPTKIT...";

    Parser parser;
    define_arguments(parser);
    parse_arguments(parser, argc, argv);
    process(parser);

    BGL bgl;

    return 1;
}

/**
 * @brief       This function is used to load parameters
 *
 * @param[in/out]       parser      This is the parameter parser
 **/
void define_arguments(Parser &parser)
{
    LOG(INFO) << "Define arguments...";
    parser.addOption(truss)
        .addOption(stmodel)
        .addOption(input)
        .addOption(output)
        .addOption(coord);
}

void parse_arguments(Parser &parser, int argc, const char* argv[])
{
    LOG(INFO) << "Parse arguments...";
    vector<string> otherArguments = parser.parse(argc, (char**)argv);

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
void process(Parser &parser)
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
            LOG(INFO) << "Initializing Crime Spatial Temporal model...";
            CrimeSTModel stm(infile.c_str());

            LOG(INFO) << "Building edges based on Crime Spatial Temporal model...";
            string coord_val = Config::instance()->get("coord");
            vector<string> _coord = Utils::split(coord_val, ',');
            vector<pair<int32_t, int32_t>> edges = stm.build_edges(stoi(_coord[0]), 
                                                                   stoi(_coord[1]), 
                                                                   stoi(_coord[2]));

            LOG(INFO) << "Building CSR based on edges...";
            // compute truss
            CSR g(edges);

            LOG(INFO) << "Start initializing truss...";
            Truss t(g.get_num_e(), g.get_num_c());

            LOG(INFO) << "Start performing truss decomposition...";
            t.truss_decomosition(g, oufile.c_str(), 5);

            LOG(INFO) << "Start getting edge list by CC...";
            // compute bgl related info
            edge_list_CC el_cc = stm.build_edge_list_CC(stoi(_coord[0]),                                                              
                                                        stoi(_coord[1]),                                                               
                                                        stoi(_coord[2]));

            DLOG(INFO) << "There are "<<el_cc.size()<<"number of CCs in total, start processing...";

            int i=0;
            for(auto it = el_cc.begin(); it != el_cc.end(); ++it)
            {
                DLOG(INFO) << "computing "<<i++<<"th CC with "<<(*it).size()<<" number of edges...";
                BGL g(*it);
                g.compute_all();
            }

            LOG(INFO)<<"Writing results to JSON file...";
            string range = _coord[0] + "," + _coord[1] + "," + _coord[2];
            Stats::instance()->write_content(Stats::RANGE, range); 
            Stats::instance()->write_content(Stats::DATANAME, infile); 
            Stats::instance()->serialize();
        }
        else
        {
            LOG(ERROR)<<"Coordinates are not specified!";
            fprintf(stderr, "You should specify coordiates!\n");
            ERROR_PRINT();
        }
    }
}
