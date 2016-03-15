/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
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

BoolOption        truss         ('t', "truss",      true , "truss apllication");
BoolOption        stmodel       ('s', "stmodel",    true , "stmodel application");
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
    parser.addOption(truss)
        .addOption(stmodel)
        .addOption(input)
        .addOption(output)
        .addOption(coord);
}

void parse_arguments(Parser &parser, int argc, const char* argv[])
{
    vector<string> otherArguments = parser.parse(argc, (char**)argv);

    string key, val;

    if(truss.isSet())
    {
        key = "application";
        val = "truss";
        Config::instance()->set(key, val);
    }
    else if(stmodel.isSet())
    {
        key = "application";
        val = "stmodel";
        Config::instance()->set(key, val);
    }

    key = "infile";
    val = input.getValue();
    Config::instance()->set(key, val);

    key = "outfile";
    val = output.getValue();
    Config::instance()->set(key, val);

    key = "coord";
    list<string> values = coord.getValue();
    int i=0;
    for(auto entry = values.begin(); i<3; i++, ++entry)
    {
        if(i>0)
        {
            val += ",";
        }
        val += *entry;
    }
    Config::instance()->set(key, val);
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
            CrimeSTModel stm(infile.c_str());
            string coord_val = Config::instance()->get("coord");
            vector<string> _coord = Utils::split(coord_val, ',');
            vector<pair<int32_t, int32_t>> edges = stm.build_edges(stoi(_coord[0]), 
                                                                   stoi(_coord[1]), 
                                                                   stoi(_coord[2]));
            CSR g(edges);
            Truss t(g.get_num_e(), g.get_num_c());
            t.truss_decomosition(g, oufile.c_str(), 5);
        }
        else
        {
            fprintf(stderr, "You should specify coordiates!\n");
            ERROR_PRINT();
        }
    }
}
