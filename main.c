/*
 * @Author: LiuHao
 * @Date: 2024-05-02 12:26:09
 * @Description: 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "parser.h"
#include "vm.h"
#include "core.h"
#include "common.h"

static void RunFile(const char *path)
{
    // path是否包含/，否则为当前路径 假设输入地址为/home/sample.spr
    const char *lastSlash = strrchr(path, '/');  // 用于判断path路径是否是当前路径的形式
    if (lastSlash != NULL) {
        char *root = (char *)malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        rootDir = root; // 将路径保存在rootDir=/home/
    }
    VM *vm = NewVMM();
    const char *sourceCode = ReadFile(path);  // 读取源码
    Parser parser;
    InitParser(vm, &parser, path, sourceCode);

    #include "scripts/sample/token.list"
    while (parser.curToken.type != TOKEN_EOF) {
        GetNextToken(&parser);
        printf("%dL: %s [", parser.curToken.lineNo, tokenArray[parser.curToken.type]);
        uint32_t idx = 0;
        while (idx < parser.curToken.length) {
            printf("%c", *(parser.curToken.start + idx ++));
        }
        printf("\n");
    }
}

int main(int argc, const char **argv)
{
    // if (argc == 1) {
    //     ;
    // } else {
    RunFile("../scripts/sample/sample.spr");
    // }
    return 0;
}