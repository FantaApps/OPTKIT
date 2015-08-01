#pragma once
#ifndef __OPTKIT_CONFIG_H__
#define __OPTKIT_CONFIG_H__

/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This file defines the class for configuration reading.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/01/15 - Creation
 *
**/


/**
 *  @class      Configuration class.
 *
 *  @brief      Read the command/parameter file, then load into this class
 *              the information for the future process.
**/
class Config
{
public:

    /**
     * @struct  mc_config
     *
     * @brief   configuration for maximum clique problem.
    **/
    struct mc_config
    {
        char *output_dir; ///< Directory to output some temporary results.
        
        /**
         * Constructor 
        **/
        mc_config()
        {
            output_dir = new char[OPTKIT_FILE_SIZE];
        }

        /**
         * Destructor 
        **/
        ~mc_config()
        {
            free(output_dir);
        }
    };

    /**
     * @struct  dis_config
     *
     * @brief   configuration for DCJ distance problem.
    **/
    struct dis_config
    {
        char *file_dict;       ///< File to store dictionary.
        char *file_bijection;  ///< File to store bijection.
        bool is_exemplar;      ///< Whether computing exemplar distance.
        bool is_cal_bij;       ///< Whether computing bijection.

        /**
         * Constructor 
        **/
        dis_config() :
            is_exe(false),
            is_cal_bij(false)
        {
            fd  = new char[OPTKIT_FILE_SIZE];
            fbi = new char[OPTKIT_FILE_SIZE];
        }

        /**
         * Destructor 
        **/
        ~dis_config()
        {
            free(fd);
            free(fbi);
        }
    };

    /**
     * @struct  knap_config
     *
     * @brief   configuration for knapsack problem.
    **/
    struct knap_config
    {
    };

    /**
     * @struct  med_config
     *
     * @brief   configuration for DCJ median problem.
    **/
    struct med_config
    {
        char *tmp_dir;   ///< Folder to store temparary results.
        int  dis_model;  ///< distance model
        int  heu_thresh; ///< Threshold for LK heuristic.
        bool use_heu;    ///< Whether using heuristic.

        /**
         * Constructor 
        **/
        med_config() :
            dm(OPTKIT_NULL),
            th(OPTKIT_NULL),
            uh(OPTKIT_NULL)
        {
            tmp_dir = new char[OPTKIT_NULL];
        }

        /**
         * Destructor 
        **/
        ~med_config() 
        {
            free(tmp_dir);
        }
    };

    
    /**
     * Constructor 
    **/
    Config() :
        num_threads(OPTKIT_NULL),
        heu_level(OPTKIT_NULL),
        term_move(OPTKIT_NULL),
        is_opt(false)
    {
        inst_logger = new char[OPTKIT_FILE_SIZE]; 
        list_logger = new char[OPTKIT_FILE_SIZE];
        input_file  = new char[OPTKIT_FILE_SIZE];
        output_file = new char[OPTKIT_FILE_SIZE];

        mc_cfg   = new mc_config();
        dis_cfg  = new dis_cfg();
        knap_cfg = new knap_cfg();
        med_cfg  = new med_cfg();
    }

    /**
     * Destructor 
    **/
    ~Config()
    {
        free(inst_logger); 
        free(list_logger);
        free(input_file);
        free(output_file);

        free(mc_cfg);
        free(dis_cfg);
        free(knap_cfg);
        free(med_cfg);
    }

    /**
     * Getters.
    **/
    const char *get_inst_logger() { return m_inst_logger; }; 
    const char *get_list_logger() { return m_list_logger; }; 
    const char *get_input_file()  { return m_input_file;  }; 
    const char *get_output_file() { return m_output_file; }; 

    int  get_num_threads() { return m_num_threads; };  
    int  get_heu_level()   { return m_heu_level;   };
    int  get_term_move()   { return m_term_move;   };
    bool get_is_opt()      { return m_is_opt;      }; 

    const mc_config   *get_mc_cfg()   { return m_mc_config;   };   
    const dis_config  *get_dis_cfg()  { return m_dis_config;  }; 
    const knap_config *get_knap_cfg() { return m_knap_config; }; 
    const med_config  *get_med_cfg()  { return m_med_config;  };  

    /**
     * Setters.
    **/
    void set_inst_logger(const char* _inst_logger) {  m_inst_logger; }; 
    void set_list_logger(const char* _list_logger) {  m_list_logger; }; 
    void set_input_file(const char*  _input_file)  {  m_input_file;  }; 
    void set_output_file(const char* _output_file) {  m_output_file; }; 

    void set_num_threads(int _num_threads) { inum_threads = num_threads; };  
    void set_heu_level(int _heu_level)   {  heu_level = heu_level;   };
    void set_term_move(int _term_move)   {  term_move = term_move;   };
    void set_is_opt(bool _is_opt)      {  is_opt = is_opt;      }; 

private:
    char *m_inst_logger; ///< Logger for instance. 
    char *m_list_logger; ///< Logger for list.
    char *m_input_file;  ///< File to read the input.
    char *m_output_file; ///< File to write output.

    int  m_num_threads;  ///< Number of threads running.

    int  m_heu_level;    ///< Level of LK heuristic.
    int  m_term_move;    ///< Termination move for LK heuristic.
    bool m_is_opt;       ///< Whether running with K-OPT algorithm.

    mc_config   *m_mc_cfg;   ///< Configuration for maximum clique.
    dis_config  *m_dis_cfg;  ///< Configuration for DCJ distance.
    knap_config *m_knap_cfg; ///< Configuration for knapsack.
    med_config  *m_med_cfg;  ///< Configuration for DCJ median.
};

#endif
