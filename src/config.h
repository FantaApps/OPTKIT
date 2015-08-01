#ifndef __OPTKIT_CONFIG_H__
#define __OPTKIT_CONFIG_H__

/**
 *  @class      ggs::ggparam::dict
 *
 *  @brief      Parameter dictionary
 *
 *  @details    This class defines an in memory dictionary that stores
 *              information of parameters that are referenced by parameter
 *              files.
**/
class config
{
public:
    struct mc_config
    {
        char *od;
    };

    struct dis_config
    {
        char *fd;
        char *fbi; 
        bool is_exe; 
        bool is_cal_bij;
    };

    struct knap_config
    {
    };

    struct med_config
    {
        char *tmp_folder;
        int  dm;
        int  th;
        bool uh;
    };

    char *lf; 
    char *f;
    char *of;
    int  heu_level;
    int  term_move;
    bool is_opt;
    int  num_t;
};

#endif
