/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
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

BoolOption    truss         ('t', "truss",      false, "perform the truss decomposition");
BoolOption    stmodel       ('s', "stmodel",    false, "perform stmodel computation");
StringOption  input         ('i', "input",      true , "input file name");
StringOption  output        ('o', "output",     true , "output file name");

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

void define_arguments(Parser &parser)
{
    parser.addOption(truss)
          .addOption(stmodel)
          .addOption(input)
          .addOption(output);
}

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
        CrimeSTModel stm(infile.c_str());
        vector<pair<int32_t, int32_t>> edges = stm.build_edges(1, 1, 1);
        CSR g(edges);
        Truss t(g.get_num_e(), g.get_num_c());
        t.truss_decomosition(g, oufile.c_str(), 5);
    }
}
