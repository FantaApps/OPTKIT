/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This file defines the class for configuration reading.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/01/15 - Creation
 *
**/

#pragma once
#ifndef __OPTKIT_CONFIG_H__
#define __OPTKIT_CONFIG_H__


enum
{
    OPTKIT_INS_MC,
    OPTKIT_INS_CC,
    OPTKIT_INS_DIS,
    OPTKIT_INS_KNAP,
    OPTKIT_INS_MED
};

enum
{
    OPTKIT_DIS_EXEM,
    OPTKIT_DIS_MATC
};

enum
{
    OPTKIT_PAR_THREAD,
    OPTKIT_PAR_BUCKET
};


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
        char* s_output_dir; ///< Directory to output some temporary results.
        
        /**
         * Constructor 
        **/
        mc_config()
        {
            s_output_dir = new char[OPTKIT_FILE_SIZE];
        }

        /**
         * Destructor 
        **/
        ~mc_config()
        {
            free(s_output_dir);
        }

        /**
         * Getters
        **/
        const char* get_output_dir() const { return s_output_dir;}

        /**
         * Setters
        **/
        void set_output_dir(const char* _output_dir) 
        {
            snprintf(s_output_dir, OPTKIT_FILE_SIZE, "%s", _output_dir);
        }
    };

    /**
     * @struct  dis_config
     *
     * @brief   configuration for DCJ distance problem.
    **/
    struct dis_config
    {
        char* s_file_dict;       ///< File to store dictionary.
        char* s_file_bijection;  ///< File to store bijection.
        bool s_is_exemplar;      ///< Whether computing exemplar distance.
        bool s_is_cal_bij;       ///< Whether computing bijection.

        /**
         * Constructor 
        **/
        dis_config() :
            s_is_exemplar(false),
            s_is_cal_bij(false)
        {
            s_file_dict      = new char[OPTKIT_FILE_SIZE];
            s_file_bijection = new char[OPTKIT_FILE_SIZE];
        }

        /**
         * Destructor 
        **/
        ~dis_config()
        {
            free(s_file_dict);
            free(s_file_bijection);
        }

        /** 
         * Getters 
        **/
        const char* get_file_dict();      const { return s_file_dict;      }
        const char* get_file_bijection(); const { return s_file_bijection; }
        bool        get_is_exemplar();    const { return s_is_exemplar;    }
        bool        get_is_cal_bij();     const { return s_is_cal_bij;     }

        /** 
         * Setters 
        **/
        void set_file_dict(const char* _file_dict)
        { 
            snprintf(s_file_dict, OPTKIT_FILE_SIZE, "%s", _file_dict);
        } 

        void set_file_bijection(const char* _file_bijection)
        { 
            snprintf(s_file_bijection, OPTKIT_FILE_SIZE, "%s", _file_bijection);
        }  

        void set_is_exemplar(int _is_exemplar)
        { 
            s_is_exemplar = _is_exemplar;
        }

        void set_is_cal_bij(int _is_cal_bij)
        { 
            s_is_cal_bij = _is_cal_bij;
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
        char* s_tmp_dir;    ///< Folder to store temparary results.
        int   s_dis_model;  ///< distance model
        int   s_heu_thresh; ///< Threshold for LK heuristic.
        bool  s_use_heu;    ///< Whether using heuristic.

        /**
         * Constructor 
        **/
        med_config() :
            s_dis_mode(OPTKIT_NULL),
            s_heu_thresh(OPTKIT_NULL),
            s_use_heu(OPTKIT_NULL)
        {
            s_tmp_dir = new char[OPTKIT_NULL];
        }

        /**
         * Destructor
        **/
        ~med_config()
        {
        }

        /** 
         * Getters 
        **/
        const char* get_tmp_dir()    const { return s_tmp_dir;    }
        int         get_dis_model()  const { return s_dis_mode;   }
        int         get_heu_thresh() const { return s_heu_thresh; }
        bool        get_use_heu()    const { return s_use_heu;    }

        /** 
         * Setters 
        **/
        void set_tmp_dir(const char* _tmp_dir)
        { 
            snprintf(s_tmp_dir, OPTKIT_FILE_SIZE, "%s", _tmp_dir);
        }

        void set_dis_model(int _dis_model)
        { 
            if(dis_model != OPTKIT_DIS_EXEM && dis_model != OPTKIT_DIS_MATC)
            {
                fprintf(stderr, "You input the wrong distance model, "
                                "please check.");
                ERROR_PRINT();
            }
            s_dis_mode = _dis_model;
        }

        void set_heu_thresh(int _heu_thresh)
        { 
            s_heu_thresh = _heu_thresh;
        }

        void set_use_heu(bool _use_heu)
        { 
            s_use_heu = _use_heu;
        }
    };

    
    /**
     * Constructor
    **/
    Config() :
        num_threads(OPTKIT_NULL),
        heu_level(2),
        term_move(3),
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
    const char* get_inst_logger() const { return m_inst_logger; }
    const char* get_list_logger() const { return m_list_logger; }
    const char* get_input_file()  const { return m_input_file;  }
    const char* get_output_file() const { return m_output_file; }
    const char* get_optim_file()  const { return m_optim_file;  }

    int  get_num_threads() const { return m_num_threads; }
    int  get_type_task()   const { return m_type_task;   }
    int  get_par_mode()    const { return m_par_mode;    }
    int  get_heu_level()   const { return m_heu_level;   }
    int  get_term_move()   const { return m_term_move;   }
    bool get_is_opt()      const { return m_is_opt;      }

    const mc_config*   get_mc_cfg()   const { return m_mc_config;   }
    const dis_config*  get_dis_cfg()  const { return m_dis_config;  }
    const knap_config* get_knap_cfg() const { return m_knap_config; }
    const med_config*  get_med_cfg()  const { return m_med_config;  }

    /**
     * Setters.
    **/
    void set_inst_logger(const char* _inst_logger) 
    {  
        snprintf(m_inst_logger, OPTKIT_FILE_SIZE, "%s", _inst_logger);
    } 

    void set_list_logger(const char* _list_logger) 
    {  
        snprintf(m_list_logger, OPTKIT_FILE_SIZE, "%s", _inst_logger);
    } 

    void set_input_file(const char*  _input_file)  
    {  
        snprintf(m_input_file, OPTKIT_FILE_SIZE, "%s", _input_file);
    } 

    void set_output_file(const char* _output_file) 
    {  
        snprintf(m_output_file, OPTKIT_FILE_SIZE, "%s", _output_file);
    } 

    void set_optim_file(const char* _optim_file) 
    {  
        snprintf(m_optim_file, OPTKIT_FILE_SIZE, "%s", _optim_file);
    } 

    void set_num_threads(int _num_threads) { m_num_threads = _num_threads; }
    void set_type_task(int _type_task)     { m_type_task   = _type_task;   }
    void set_par_mode(int _par_mode)       { m_par_mode    = _par_mode;    }
    void set_heu_level(int _heu_level)     { m_heu_level   = _heu_level;   }
    void set_term_move(int _term_move)     { m_term_move   = _term_move;   }
    void set_is_opt(bool _is_opt)          { m_is_opt      = _is_opt;      }

private:

    char* m_inst_logger; ///< Logger for instance.
    char* m_list_logger; ///< Logger for list.
    char* m_input_file;  ///< File to read the input.
    char* m_output_file; ///< File to write output.
    char* m_optim_file;  ///< File to write optimal results.

    int  m_num_threads;  ///< Number of threads running.
    int  m_type_task;    ///< Indicate which task is running.
    int  m_par_mode;     ///< parallel mode, thread or bucket.

    int  m_heu_level;    ///< Level of LK heuristic.
    int  m_term_move;    ///< Termination move for LK heuristic.
    bool m_is_opt;       ///< Whether running with K-OPT algorithm.

    mc_config   *m_mc_cfg;   ///< Configuration for maximum clique.
    dis_config  *m_dis_cfg;  ///< Configuration for DCJ distance.
    knap_config *m_knap_cfg; ///< Configuration for knapsack.
    med_config  *m_med_cfg;  ///< Configuration for DCJ median.
};

#endif
