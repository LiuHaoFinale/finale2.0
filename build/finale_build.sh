#!/bin/bash

###
 # @Author: LiuHao
 # @Date: 2024-04-21 00:41:22
 # @Description: 
### 

# 删除之前的文件
shopt -s extglob
# 删除除 finale_build.sh 外的所有文件和文件夹
find . -mindepth 1 ! -name 'finale_build.sh' -type f -exec rm -f {} +
find . -mindepth 1 ! -name 'finale_build.sh' -type d -exec rm -rf {} +

echo "Cleanup completed."

# 执行构建命令
cmake ..
cmake --build .