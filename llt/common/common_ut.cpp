/*
 * @Author: LiuHao
 * @Date: 2024-05-03 14:24:19
 * @Description: 
 */
#include "gtest/gtest.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#include "parser.h"
#include "vm.h"
#include "common.h"
#include "utils.h"
}

class CommonLibTest: public ::testing::Test {
    protected:
        void SetUp() override
        {

        }

        void TearDown() override
        {

        }
};

TEST_F(CommonLibTest, GetSystemTimeTest)
{
    const char *localTime = const_cast<const char *>(GetSystemTime());
    std::cout << localTime<< std::endl;
}

#endif