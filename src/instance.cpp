#include "instance.h"
#include <cstdio>


Instance::Instance()
{
    upper_bound = 0;
    lower_bound = 0;
    control = false;
}

Instance::Instance(const Instance &other)
{
    upper_bound = other.upper_bound;
    lower_bound = other.lower_bound;
}


Instance::Instance(const char* lf) 
{
    logger = NULL;
    if(lf != NULL)
    {
        if((logger = fopen(lf, "w")) == NULL)
        {
            printf("the file %s you input does not exist!\n", lf);
            exit(1);
        }
    }
}

/**
 * Factory pattern implementation.
**/
Instance *make_instance(int choice, const char *f, const char *od, const char *lf)
{
    if(choice == OPTKIT_INS_MC)
    {
        return new InsMC(f, od, lf);
    }
    else if(choice == OPTKIT_INS_DIS)
    {
        return new InsDis(f, is_exe, lf, const char* fd, const char* fbi, const bool *is_cal_bij) : 
    }
    else if(choice == OPTKIT_INS_KNAP)
    {
    }
    else if(choice == OPTKIT_INS_MED)
    {
    }
}

/**
 * Virtual functions.
**/
Instance::~Instance(){}
void Instance::to_branch(int which_branch){}
void Instance::from_branch(){}
void Instance::compute_bound(){}
int  Instance::get_num_branches(){return 0;}
int  Instance::get_encode(int *encode){return 0;}
void Instance::to_encode(int *encode, int size){}
void Instance::print_encode(){}
void Instance::copy_code(int *encode, int size){}
int  Instance::get_value(){return 0;}
int  Instance::return_private_info(){return 0;}
