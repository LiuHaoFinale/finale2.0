/*
 * @Author: LiuHao
 * @Date: 2024-05-02 13:33:22
 * @Description: 
 */
#include "gtest/gtest.h"
#include "vm.h"

class VMMainClass: public ::testing::Test {
    protected:
        void SetUp() override
        {

        }

        void TearDown() override
        {

        }
};

TEST_F(VMMainClass, InitTest)
{
    EXPECT_EQ(NUM_TEST, 2U);
}

TEST_F(VMMainClass, InitTest2)
{
    EXPECT_EQ(NUM_TEST, 2U);
}

TEST_F(VMMainClass, InitTest3)
{
    EXPECT_EQ(NUM_TEST, 2U);
}