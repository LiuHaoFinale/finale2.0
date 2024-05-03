# !/bin/zsh

###
 # @Author: LiuHao
 # @Date: 2024-05-02 13:44:26
 # @Description: 
###

# TODO:初始版本，仅作为简单测试用

cd build
echo "$(pwd)"
echo -e "y" | rm -rf ./* # 在zsh环境下需要自动输入y
# rm -rf ./* # 在bash环境下使用此命令
cmake ..