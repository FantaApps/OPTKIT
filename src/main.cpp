#include "list.h"
#include "insknap.h"
#include "insmed.h"
#include "insmc.h"
#include "listint.h"
#include "instance.h"
#include "plist.h"
#include "insdis.h"
#include <getopt.h>


static int verbose_flag;
void
print_help();

int parallel_mode = -1;

int which_med;


#define DIS_MODE_EXEM 1
#define DIS_MODE_MATC 2

int main(int argc , char *argv[]){

    int seq_len;
    bool is_CC_separation = false;
    bool is_dis           = false;
    bool is_dcj           = false;
    bool is_med           = false;
    bool is_knap          = false;
    bool is_mc            = false;
    bool is_cal_bij       = false;
    int heu_level         = 2;
    int term_move         = 3;
    bool is_opt           = false;
    char *input_file      = NULL;
    char *output_file     = NULL;
    char *output_dir      = NULL;
    char *bij_file        = NULL;
    char *dict_file       = NULL;
    char *tmp_folder      = NULL;
    int dis_mode          = 1;
    int num_t             = 1;
    int c                 = -1;
    char *opt_file        = NULL;
    char *logger_path     = NULL;

    while (1)
    {
        static struct option long_options[] =
        {   
            /* These options set a flag. */
            {"verbose",     no_argument,       &verbose_flag, 1}, 
            {"brief",       no_argument,       &verbose_flag, 0}, 
            /* These options don't set a flag.
             * We distinguish them by their indices. */
            {"dis",         no_argument,             0, 'D'},
            {"dcj",         no_argument,             0, 'd'},
            {"median",      no_argument,             0, 'm'},
            {"knap",        no_argument,             0, 'k'},
            {"cal_bij",     no_argument,             0, 'j'},
            {"mc",          no_argument,             0, 'C'},
            {"CC",          no_argument,             0, 'c'},
            {"dis_mode",	required_argument, 	     0, 'M'},
            {"num_t",       required_argument,       0, 't'},
            {"input_file",  required_argument,       0, 'f'},
            {"output_file", required_argument,       0, 'F'},
            {"bij_file",    required_argument,       0, 'J'},
            {"dict_file",   required_argument,       0, 'T'},
            {"output_dir",  required_argument,       0, 'r'},
            {"p_mode",      required_argument,       0, 'p'},
            {"heu_level",   required_argument,       0, 'l'},
            {"term_move",   required_argument,       0, 'v'},
            {"is_opt",      required_argument,       0, 'o'},
            {"opt_file",    required_argument,       0, 'O'},
            {"seq_len",     required_argument,       0, 'L'},
            {"tmp_folder",  required_argument,       0, '1'},
            {"logger_path", required_argument,       0, '2'},
            {"help",        no_argument,             0, 'h'},
            {0,             0,                       0,  0 }
        }; 
        int option_index = 0;
        c = getopt_long (argc, argv, "df:hjJ:kl:mo:p:t:T:v:1:", 
                long_options, &option_index);
        if (c == -1)
            break;	
        switch (c)
        {
            case 'r':
                {
                    output_dir = optarg;
                    break;
                }
            case 'D':
                {
                    is_dis = true;
                    break;
                }
            case 'L':
                {
                    seq_len = atoi(optarg);
                    break;
                }
            case 'M':
                {
                    dis_mode = atoi(optarg);
                    break;
                }
            case 'd':
                {
                    is_dcj = true;
                    break;
                }
            case 'f':
                {
                    input_file = optarg;
                    break;
                }
            case 'j':
                {
                    is_cal_bij = true;
                    break;
                }
            case 'J':
                {
                    bij_file = optarg;
                    break;
                }
            case 'F':
                {
                    output_file = optarg;
                    break;
                }
            case 'O':
                {
                    opt_file = optarg;
                    break;
                }
            case 'h':
                {
                    print_help();
                    return 1;
                }
            case 'k':
                {
                    is_knap = true;
                    break;
                }
            case 'l':
                {
                    heu_level = atoi(optarg);
                    break;
                }
            case 'm':
                {
                    is_med = true;
                    break;
                }
            case 'C':
                {
                    is_mc = true;
                    break;
                }
            case 'c':
                {
                    is_CC_separation = true;
                    break;
                }
            case 'o':
                {
                    is_opt = atoi(optarg)==0?true:false; 
                    break;
                }
            case 'p':
                {
                    parallel_mode = atoi(optarg);
                    break;
                }
            case 't':
                {
                    num_t = atoi(optarg);
                    break;
                }
            case 'T':
                {
                    dict_file = optarg;
                    break;
                }
            case 'v':
                {
                    term_move = atoi(optarg);
                    break;
                }
            case '1':
                {
                    tmp_folder = optarg;
                    break;
                }
            case '2':
                {
                    logger_path = optarg;
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

void process_options()
{
}

void execute_seq()
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
