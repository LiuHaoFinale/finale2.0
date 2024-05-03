cmake_minimum_required(VERSION 3.1)

project(finale)

set(FINALE_COMPILER_INC
    $ENV{TOP_SOURCE}/compiler
    $ENV{TOP_SOURCE}/compiler/structure
    $ENV{TOP_SOURCE}/compiler/assist
    $ENV{TOP_SOURCE}/compiler/oper
)

set(FINALE_VMM_INC
    $ENV{TOP_SOURCE}/vm
    $ENV{TOP_SOURCE}/vm/alloc
    $ENV{TOP_SOURCE}/vm/core
    $ENV{TOP_SOURCE}/vm/prim
    $ENV{TOP_SOURCE}/vm/exec
)

set(FINALE_CLASS_INC
    $ENV{TOP_SOURCE}/class
    $ENV{TOP_SOURCE}/class/include
)

set(FINALE_PARSER_INC
    $ENV{TOP_SOURCE}/parser
)

set(FINALE_COMMON_INC
    $ENV{TOP_SOURCE}/gc # GC
    $ENV{TOP_SOURCE}/common
    $ENV{TOP_SOURCE}/common/merror
    $ENV{TOP_SOURCE}/common/unicode
    $ENV{TOP_SOURCE}/common/lhlog
)

include_directories(
    ${FINALE_COMMON_INC}
    ${FINALE_COMPILER_INC}
    ${FINALE_VMM_INC}
    ${FINALE_CLASS_INC}
    ${FINALE_PARSER_INC}
) # finale include

aux_source_directory(. COMPILER_DIR)

add_library(
    compiler
    STATIC
    ${COMPILER_DIR}
)