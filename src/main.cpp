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
#include "../libs/Parser.h"
#include "csr.h"
#include "truss.h"
#include "CrimeSTModel.h"
#include <getopt.h>

void define_arguments(Parser &parser);
void process(Parser &parser);

BoolOption        truss         ('t', "truss",      false, "perform the truss decomposition");
BoolOption        stmodel       ('s', "stmodel",    false, "perform stmodel computation");
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
    process(parser);

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
            list<string> values = coord.getValue();
            int     _coord[3];
            uint8_t i = 0;

            for(auto entry = values.begin(); entry != values.end(); ++entry) 
            {
                _coord[i++] = stoi(*entry);
            }

            CrimeSTModel stm(infile.c_str());
            vector<pair<int32_t, int32_t>> edges = stm.build_edges(_coord[0], _coord[1], _coord[2]);
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
