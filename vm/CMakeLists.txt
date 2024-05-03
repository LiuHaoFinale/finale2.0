cmake_minimum_required(VERSION 3.1)

project(finale)

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

aux_source_directory(. VMM_DIR)

add_library(
    vmm
    STATIC
    ${VMM_DIR}
)