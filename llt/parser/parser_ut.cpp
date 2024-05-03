/*
 * @Author: LiuHao
 * @Date: 2024-05-03 01:30:47
 * @Description:
 */
#include "gtest/gtest.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#include "parser.h"
#include "vm.h"
#include "common.h"
#include "token.h"
#include <stdlib.h>
}

const char *g_sourceCode = "import";
const char *g_path = "sample.spr";

class ParserUTClass: public ::testing::Test {
    protected:
        void SetUp() override
        {
            vmm = NewVMM(); // 新建vmm
            InitParser(vmm, &parser, g_path, g_sourceCode, NULL); // 新建Parser
        }

        void TearDown() override
        {
            free(vmm);
            vmm = NULL;
        }
    public:
        VM *vmm;
        Parser parser;
};

TEST_F(ParserUTClass, GetNextTokenTest)
{
    GetNextToken(&parser);
    EXPECT_EQ(parser.curToken.type, TOKEN_IMPORT);
}
#endif