cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 13.02_Extended_BST)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

find_path(TREE_HEADER NAMES ST.h PATHS
"${CMAKE_FRAMEWORK_PATH}../../../13_Balanced_trees/13.00_Balanced_trees/examples")
include_directories(${TREE_HEADER})
message(STATUS "TREE_HEADER=${TREE_HEADER}")

add_executable(${THIS_PROJECT} ex_13_5.cpp)

set_target_properties(${THIS_PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${THIS_PROJECT} PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    target_compile_options(${THIS_PROJECT} PRIVATE
        /W4
    )
else ()
    target_compile_options(${THIS_PROJECT} PRIVATE
        -Wall -Wextra -pedantic -Werror -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
    )
endif()