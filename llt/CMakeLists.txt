cmake_minimum_required(VERSION 3.1)
project(finale)

# execute_process(COMMAND sh -c "rm -rf ./*")

# execute_process(COMMAND sh -c "")

function(build_project path)
    # 执行命令，这里使用 sh -c 来执行多条命令
    execute_process(
        COMMAND sh -c "cmake ../${path}/ && cmake --build ."
    )
endfunction()

# build_project("vm")
# build_project("class")
# build_project("compiler")
# build_project("gc")
# build_project("parser")
build_project("common")