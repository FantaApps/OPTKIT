/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Test the main function for regression
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   07/24/16 - Creation
**/

#include <gtest/gtest.h>
#include <stdlib.h>
#include "test_util.h" 

/**
 * @brief   Test running NY crime data without saving context 
 *
**/
TEST(NYCrime_Regression_Test_1, Success)
{
    int status = system("../src/optkit --stmodel --bgl " 
                        " -i ../data/truss/ny_crime.csv "
                        " -o ../data/experiments/stmodel/ny_crime_100_100_0 "
                        " -c 100 -c 100 -c 0 "
                        " -l ny_crime_100_100_0_");


    exit(1);
    ASSERT_EQ(status, 0);

    // check results 
    ASSERT_EQ(TstUtil::compareFile("../data/experiments/stmodel/ny_crime_100_100_0.json",
                                   "../QA/testcase/results/ny_crime_100_100_0.json", 
                                   true), 
                                   TstUtil::OPTKIT_TEST_PASS); 
    std::remove("../data/experiments/stmodel/ny_crime_100_100_0.json");
    // check logs
}
