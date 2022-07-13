cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 12.09_BST_implementations_of_other_adt_functions)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

add_executable(ex_12_78 ex_12_78.cpp)

set(PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include_directories("${CMAKE_BINARY_DIR}")