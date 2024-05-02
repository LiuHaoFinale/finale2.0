#!/bin/bash
###
 # @Author: LiuHao
 # @Date: 2024-04-21 00:41:22
 # @Description: 
### 

# 检查参数是否存在
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <type>"
    exit 1
fi

# 获取参数
type="$1"

# 设置默认的构建目标
target="finale"

# 根据参数设置不同的构建目标
if [ "$type" == "lex" ]; then
    target="finale_lex"
elif [ "$type" == "grammar" ]; then
    target="finale_grammar"
fi

# 删除之前的文件
shopt -s extglob
# 删除除 rm_build.sh 外的所有文件和文件夹
find . -mindepth 1 ! -name 'rm_build.sh' -type f -exec rm -f {} +
find . -mindepth 1 ! -name 'rm_build.sh' -type d -exec rm -rf {} +

echo "Cleanup completed."

# 输出当前的目标
echo "Building target: $target"

# 执行构建命令
cmake ..
cmake --build . --target "$target"

# 检查构建结果
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

exit 0
