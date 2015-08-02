/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the main entry of OPTKIT. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/01/15 - Creation
 *
**/

#include "utils.h"
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

#include <getopt.h>


void process_options(Config *cfg);
void execute_sequential();
void print_help();


int main(int argc , char *argv[])
{
    Config *cfg = new Config();
    process_options(cfg);
    return 0;
}

void process_options(Config *cfg)
{
    static int verbose_flag;
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
            {0,             0,                       0,  0 }
        }; 

        int option_index = 0;
        c = getopt_long (argc, argv, "b:cCd:D1:hH:i:I:2:kl:mMn:o:O:3:p:t:T:"
                long_options, &option_index);
        if (c == -1)
            break;	
        switch (c)
        {
            case 'b':
                {
                    config->get_dis_cfg()->set_file_bijection(optarg);
                    break;
                }
            case 'c':
                {
                    config->get_dis_cfg()->set_is_cal_bij(true);
                    break;
                }
            case 'C':
                {
                    config->set_type_task(OPTKIT_INS_CC);
                    break;
                }
            case 'd':
                {
                    config->get_dis_cfg()->set_file_dict(optarg);
                    break;
                }
            case 'D':
                {
                    config->set_type_task(OPTKIT_INS_DIS);
                    break;
                }
            case '1':
                {
                    config->get_med_cfg()->set_dis_model(atoi(optarg));
                    break;
                }
            case 'h':
                {
                    print_help();
                    return 1;
                }
            case 'H':
                {
                    config->set_heu_level(atoi(optarg));
                    break;
                }
            case 'i':
                {
                    config->set_input_file(optarg);
                    break;
                }
            case 'I':
                {
                    config->set_inst_logger(optarg);
                    break;
                }
            case '2':
                {
                    config->set_is_opt(true);
                    break;
                }
            case 'k':
                {
                    config->set_type_task(OPTKIT_INS_KNAP);
                    break;
                }
            case 'l':
                {
                    config->set_list_logger(optarg);
                    break;
                }
            case 'm':
                {
                    config->set_type_task(OPTKIT_INS_MED);
                    break;
                }
            case 'M':
                {
                    config->set_type_task(OPTKIT_INS_MC);
                    break;
                }
            case 'n':
                {
                    config->set_num_threads(atoi(optarg));
                    break;
                }
            case 'o':
                {
                    config->set_optim_file(optarg);
                    break;
                }
            case 'O':
                {
                    config->set_output_file(optarg);
                    break;
                }
            case '3':
                {
                    config->get_mc_cfg()->set_output_dir(optarg);
                    break;
                }
            case 'p':
                {
                    config->set_par_mode(atoi(optarg));
                    break;
                }
            case 't':
                {
                    config->set_term_move(atoi(optarg));
                    break;
                }
            case 'T':
                {
                    config->get_med_cfg()->set_tmp_dir(optarg);
                    break;
                }
            case '?':
                {
                    print_help();
                    return 1;
                }
            default:
                {
                    abort ();
                }
        }
    }
}

void execute_sequential()
{
        printf("Start initialization of MC instances...\n");

        Instance** ins = new InsMC*[2];
        if(logger_path != NULL)
        {
            char condated[OPTKIT_FILE_SIZE];
            Utils::concate_path(logger_path, input_file, OPTKIT_FILE_SIZE, concated, OPTKIT_FILE_SIZE);
            ins[0] = new InsMC(input_file, NULL, lf_insmc);
        }
        ins[1] = new InsMC(input_file);

        printf("finished initialization of instances!\n");

        printf("Start allocating search list...\n");

        int buck_size    = ins[0]->upper_bound - ins[0]->lower_bound + 2;
        int list_size    = 100000;
        int base         = ins[0]->lower_bound-1;
        int num_t        = 1;
        int num_elem     = ins[0]->num_count;
        bool is_ub       = true;
        bool is_enum_all = true;
        IntList *list = new IntList(buck_size, list_size, 
                                    base,      num_t, 
                                    is_ub,     num_elem, 
                                    &is_enum_all);

        printf("Start allocating search list...\n");

        list->bnb(ins, 0);
}

void print_help()
{
    FILE *reader = fopen("./HELP.txt", "r");
    if(reader == NULL)
    {
        printf("the file %s does not exists!\n", "HELP.txt");
        exit(1);
    }
    /* obtain file size: */
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    /* allocate memory to contain the whole file: */
    buffer = new char[lSize];
    if (buffer == NULL) 
    {
        fputs ("Memory error",stderr); 
        exit (2);
    }

    /* copy the file into the buffer: */
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) 
    {
        fputs ("Reading error",stderr); 
        exit (3);
    }

    /* the whole file is now loaded in the memory buffer. */
    printf("%s", buffer);

    /* terminate */
    fclose (pFile);
    free (buffer);
}
