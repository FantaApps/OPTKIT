/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   12/13/15 - Fixed bugs related to print_help() 
 *  stplaydog   08/02/15 - Fixed bugs to make it compile.
 *  stplaydog   08/01/15 - Creation
 *
**/

#include "utils.h"
#include "graph_util.h"
#include "config.h"
#include "factory.h"

#include "list.h"
#include "listint.h"
#include "plist.h"

#include "instance.h"
#include "insdis.h"
#include "insknap.h"
#include "insmed.h"
#include "insmc.h"

#include "csr.h"
#include "truss.h"

#include <getopt.h>


int32_t  process_options(int32_t argc, char* argv[], Config *cfg);
void execute_sequential();
void execute_graph_utils(const Config *cfg);
void execute_truss_decomposition(const Config *cfg);
void print_help();

/**
 * Main function of OPTKIT
**/
int32_t main(int32_t argc , char *argv[])
{
    Config *cfg = new Config();
    int32_t ret = process_options(argc, argv, cfg);
    return ret;
}

/**
 * Process to command line options for OPTKIT.
 *
 * @param[in]       argc        Number of arguments.
 * @param[in]       argv        Arguments in the form of array.
 * @param[in]       cfg         Configuration file.
 *
 * @return      N/A
**/
int32_t process_options(int32_t argc, char* argv[], Config *cfg)
{
    static int32_t verbose_flag;
    while (1)
    {
        static struct option long_options[] =
        {   
            /* These options set a flag. */
            {"verbose",     no_argument,       &verbose_flag, 1}, 
            {"brief",       no_argument,       &verbose_flag, 0}, 
            /* These options don't set a flag.
             * We distinguish them by their indices. */
            {"bij_file",    required_argument,       0, 'b'},
            {"cal_bij",     no_argument,             0, 'c'},
            {"CC",          no_argument,             0, 'C'},
            {"dict_file",   required_argument,       0, 'd'},
            {"dis",         no_argument,             0, 'D'},
            {"dis_mode",	required_argument, 	     0, '1'},
            {"help",        no_argument,             0, 'h'},
            {"heu_level",   required_argument,       0, 'H'},
            {"input_file",  required_argument,       0, 'i'},
            {"inst_logger", required_argument,       0, 'I'},
            {"is_opt",      no_argument,             0, '2'},
            {"knap",        no_argument,             0, 'k'},
            {"list_logger", required_argument,       0, 'l'},
            {"median",      no_argument,             0, 'm'},
            {"mc",          no_argument,             0, 'M'},
            {"num_t",       required_argument,       0, 'n'},
            {"opt_file",    required_argument,       0, 'o'},
            {"output_file", required_argument,       0, 'O'},
            {"output_dir",  required_argument,       0, '3'},
            {"p_mode",      required_argument,       0, 'p'},
            {"term_move",   required_argument,       0, 't'},
            {"tmp_folder",  required_argument,       0, 'T'},
            {"truss",       required_argument,       0, '4'},
            {0,             0,                       0,  0 }
        }; 

        int32_t option_index = 0;
        int32_t c = getopt_long (argc, argv, "b:cCd:D1:hH:i:I:2:kl:mMn:o:O:3:p:t:T:4",
                long_options, &option_index);
        if (c == OPTKIT_NULL)
        {
            print_help();
            break;	
        }
        switch (c)
        {
            case 'b':
                {
                    cfg->get_dis_cfg()->set_file_bijection(optarg);
                    break;
                }
            case 'c':
                {
                    cfg->get_dis_cfg()->set_is_cal_bij(true);
                    break;
                }
            case 'C':
                {
                    cfg->set_type_task(OPTKIT_INS_CC);
                    break;
                }
            case 'd':
                {
                    cfg->get_dis_cfg()->set_file_dict(optarg);
                    break;
                }
            case 'D':
                {
                    cfg->set_type_task(OPTKIT_INS_DIS);
                    break;
                }
            case '1':
                {
                    cfg->get_med_cfg()->set_dis_model(atoi(optarg));
                    break;
                }
            case 'h':
                {
                    print_help();
                    return 1;
                }
            case 'H':
                {
                    cfg->set_heu_level(atoi(optarg));
                    break;
                }
            case 'i':
                {
                    cfg->set_input_file(optarg);
                    break;
                }
            case 'I':
                {
                    cfg->set_inst_logger(optarg);
                    break;
                }
            case '2':
                {
                    cfg->set_is_opt(true);
                    break;
                }
            case 'k':
                {
                    cfg->set_type_task(OPTKIT_INS_KNAP);
                    break;
                }
            case 'l':
                {
                    cfg->set_list_logger(optarg);
                    break;
                }
            case 'm':
                {
                    cfg->set_type_task(OPTKIT_INS_MED);
                    break;
                }
            case 'M':
                {
                    cfg->set_type_task(OPTKIT_INS_MC);
                    break;
                }
            case 'n':
                {
                    cfg->set_num_threads(atoi(optarg));
                    break;
                }
            case 'o':
                {
                    cfg->set_optim_file(optarg);
                    break;
                }
            case 'O':
                {
                    cfg->set_output_file(optarg);
                    break;
                }
            case '3':
                {
                    cfg->get_mc_cfg()->set_output_dir(optarg);
                    break;
                }
            case 'p':
                {
                    cfg->set_par_mode(atoi(optarg));
                    break;
                }
            case 't':
                {
                    cfg->set_term_move(atoi(optarg));
                    break;
                }
            case 'T':
                {
                    cfg->get_med_cfg()->set_tmp_dir(optarg);
                    break;
                }
            case '5':
                {
                    cfg->set_type_task(OPTKIT_INS_TRUSS);
                    break;
                }
            case '?':
                {
                    print_help();
                    return 1;
                }
            default:
                {
                    print_help();
                    abort ();
                }
        }
    }

    if(cfg->get_type_task() == OPTKIT_INS_CC) 
    {
        execute_graph_utils(cfg);
    }
    else if(cfg->get_type_task() == OPTKIT_INS_TRUSS) 
    {
        execute_graph_utils(cfg);
    }

    return 1;
}

void execute_graph_utils(const Config *cfg)
{
    GraphUtils::connected_comps(cfg->get_input_file(), 
            cfg->get_mc_cfg()->get_output_dir());
}

void execute_truss_decomposition(const Config *cfg)
{
    CSR g(cfg->get_input_file());
}

void execute_sequential()
{
    //printf("Start initialization of MC instances...\n");

    //Instance** ins = new InsMC*[2];
    //if(logger_path != NULL)
    //{
    //    char condated[OPTKIT_FILE_SIZE];
    //    Utils::concate_path(logger_path, input_file, OPTKIT_FILE_SIZE, concated, OPTKIT_FILE_SIZE);
    //    ins[0] = new InsMC(input_file, NULL, lf_insmc);
    //}
    //ins[1] = new InsMC(input_file);

    //printf("finished initialization of instances!\n");

    //printf("Start allocating search list...\n");

    //int32_t buck_size    = ins[0]->upper_bound - ins[0]->lower_bound + 2;
    //int32_t list_size    = 100000;
    //int32_t base         = ins[0]->lower_bound-1;
    //int32_t num_t        = 1;
    //int32_t num_elem     = ins[0]->num_count;
    //bool is_ub       = true;
    //bool is_enum_all = true;
    //IntList *list = new IntList(buck_size, list_size, 
    //                            base,      num_t, 
    //                            is_ub,     num_elem, 
    //                            &is_enum_all);

    //printf("Start allocating search list...\n");

    //list->bnb(ins, 0);
}


/**
 * @brief   print the instruction of how to use OPTKIT
 *
**/
void print_help()
{
    FILE *reader = fopen("./HELP.txt", "r");
    if(reader == NULL)
    {
        printf("the file %s does not exists!\n", "HELP.txt");
        ERROR_PRINT();
    }
    /* obtain file size: */
    fseek (reader, 0 , SEEK_END);
    size_t lSize = ftell (reader);
    rewind (reader);
    /* allocate memory to contain the whole file: */
    char *buffer = new char[lSize];
    if (buffer == NULL) 
    {
        fputs ("Memory error",stderr); 
        ERROR_PRINT();
    }

    /* copy the file into the buffer: */
    size_t result = fread (buffer,1,lSize,reader);
    if (result != lSize) 
    {
        fputs ("Reading error",stderr); 
        ERROR_PRINT();
    }

    /* the whole file is now loaded in the memory buffer. */
    printf("%s\n", buffer);

    /* terminate */
    fclose (reader);
    free (buffer);
}
