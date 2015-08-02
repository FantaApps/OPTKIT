/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Basic instance implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Creation
**/

#include "instance.h"

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
