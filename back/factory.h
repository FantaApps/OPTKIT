/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This file defines the class for factory purpose.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Modified according to new standard of config.h
 *  stplaydog   08/01/15 - Creation
 *
**/

#pragma once
#ifndef _H_INSDIS
#define _H_INSDIS

#include "instance.h"
#include "insmc.h"
#include "insknap.h"
#include "insmed.h"
#include "insdis.h"
#include "utils.h"
#include "config.h"


/**
 * @class Factory implementation 
 *
 * This class implements some of the factory methods in OPTKIT. 
 * 
**/
class Factory {
public:

    /**
     * Factory implementation for instances.
     *
     * @param[in]       cfg         configuration object.
     *
     * @return      N/A
    **/
    Instance* make_instance(Config *cfg)
    {
        int choice = cfg->get_type_task();

        if(choice == OPTKIT_INS_MC)
        {
            //TODO some detailing here.
            return new InsMC(cfg->get_input_file(), 
                             cfg->get_mc_cfg()->get_output_dir(), 
                             cfg->get_inst_logger());
        }
        else if(choice == OPTKIT_INS_DIS)
        {
            // TODO some detailing here.
            //return new InsDis(cfg->get_input_file(), 
            //                  cfg->get_dis_cfg()->get_is_exemplar(), 
            //                  cfg->get_inst_logger(),
            //                  cfg->get_dis_cfg()->get_file_dict(),
            //                  cfg->get_dis_cfg()->get_file_bijection(), 
            //                  cfg->get_dis_cfg()->get_is_cal_bij());
        }
        else if(choice == OPTKIT_INS_KNAP)
        {
            // TODO some detailing here.
            //return new InsMC(cfg->get_input_file(), 
            //                 0,
            //                 cfg->get_inst_logger());
        }
        else if(choice == OPTKIT_INS_MED)
        {
            //TODO some detailing here.
            //return new InsMed(cfg->get_input_file(), 
            //                 cfg->get_med_cfg()->get_tmp_dir(), 
            //                 0,
            //                 cfg->get_inst_logger()
            //                 cfg->get_med_cfg()->get_dis_model(),
            //                 cfg->get_med_cfg()->get_use_heu(),
            //                 cfg->get_med_cfg()->get_heu_thresh());
        }
    }
};

#endif
