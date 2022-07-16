cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 14.02_Separate_binding)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

find_path(ITEM_HEADER NAMES Item.h PATHS
"${CMAKE_FRAMEWORK_PATH}../../../13_Balanced_trees/13.00_Balanced_trees/examples")

find_path(HASH_HEADER NAMES Hash.h PATHS
"${CMAKE_FRAMEWORK_PATH}../../../14_Hashing/14.01_Hash_functions/examples")
include_directories(${HASH_HEADER} ${ITEM_HEADER})

add_executable(${THIS_PROJECT} ex_14_3.cpp)

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