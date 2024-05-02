cmake_minimum_required(VERSION 3.1)

project(finale)

set(FINALE_INC
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/gc
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/parser
)

set(FINALE_SUB_DIR
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/gc
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/parser
)

# TODO:=========仅做临时测试用，后期将其作为链接库使用==================

set(FINALE_SRC_DIR
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/gc
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/parser
)

set(FINALE_SRC "")

foreach(dir ${FINALE_SRC_DIR})
    aux_source_directory(${dir} DIR_SRC)
    list(APPEND $FINALE_SRC ${DIR_SRC})
endforeach()

# ===================================================================

set(CLOG_INC
    $ENV{TOP_SOURCE}/open_soruce/clog/include
)

add_compile_definitions(FINALE_LOG)

include_directories(${CLOG_INC})

add_executable(finale main.c ${FINALE_SRC})

# add_subdirectory(${FINALE_SUB_DIR})

set_target_properties(finale PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)

# target_include_directories(${FINALE_INC})

# target_link_libraries(finale libvm.a)