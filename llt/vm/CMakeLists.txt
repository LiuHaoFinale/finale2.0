cmake_minimum_required(VERSION 3.1)

project(finale)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake")

# 查找 libtest 静态库和头文件
find_package(libgtest REQUIRED)

set(FINALE_SRC_DIR
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/vm/alloc
    $ENV{TOP_SOURCE}/vm/core
    $ENV{TOP_SOURCE}/vm/prim
    $ENV{TOP_SOURCE}/vm/exec
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/class/object
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/gc
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/common/merror
    $ENV{TOP_SOURCE}/common/unicode
    $ENV{TOP_SOURCE}/common/lhlog
    $ENV{TOP_SOURCE}/parser
)

set(FINALE_SRC "")

foreach(dir ${FINALE_SRC_DIR})
    aux_source_directory(${dir} DIR_SRC)
    list(APPEND FINALE_SRC ${DIR_SRC})
endforeach()

# set(GTEST_INC)
set(VM_SRC
    ${CMAKE_SOURCE_DIR}/vm_ut.cpp
)
set(VM_INC
    ${CMAKE_SOURCE_DIR}
)

set(FINALE_INC
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/vm/alloc
    $ENV{TOP_SOURCE}/vm/core
    $ENV{TOP_SOURCE}/vm/prim
    $ENV{TOP_SOURCE}/vm/exec
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/class/include
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/gc
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/common/merror
    $ENV{TOP_SOURCE}/common/unicode
    $ENV{TOP_SOURCE}/common/lhlog
    $ENV{TOP_SOURCE}/parser
)

include_directories(${FINALE_INC}) # finale include
include_directories(${VM_INC}) # gtest include

# 添加项目目标
add_executable(gtest_vm_app
    main_ut.cpp
    ${FINALE_SRC}
    ${VM_SRC}
)

set_target_properties(gtest_vm_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含 libtest 头文件路径
target_include_directories(gtest_vm_app PRIVATE ${libgtest_INCLUDE_DIRS})

# 链接 libtest 静态库
target_link_libraries(gtest_vm_app PRIVATE ${libgtest_LIBRARIES})