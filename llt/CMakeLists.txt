cmake_minimum_required(VERSION 3.1)
project(finale)

function(build_project path)
    # 执行命令，这里使用 sh -c 来执行多条命令
    execute_process(
        COMMAND sh -c "rm -rf ./* && cmake ../${path}/ && cmake --build ."
    )
endfunction()

build_project("vm")