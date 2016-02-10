/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/01/16 - Creation
**/

#include <gtest/gtest.h>
#include "STModel.h"
#include "CrimeSTModel.h" 
#include "test_util.h" 

using namespace std;

/**
 * @brief   Test a small graph one color
 *
**/
TEST(NYCrimeDataTest_1, Success)
{
    string input_file = "../data/truss/ny_crime.csv"; 
    CrimeSTModel stm(input_file);
    stm.serialize();

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/crime_data.txt", "./crime_data.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./crime_data.txt");
}

