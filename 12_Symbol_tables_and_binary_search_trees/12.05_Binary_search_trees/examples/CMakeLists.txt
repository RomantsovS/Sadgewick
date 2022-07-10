cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 12.05_Binary_search_trees)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

add_executable(${THIS_PROJECT} ex_12_8.cpp)
add_executable(ex_12_9 ex_12_9.cpp)
add_executable(ex_12_10 ex_12_10.cpp)

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
        -Wall -Wextra -pedantic -Werror
    )
endif()