cmake_minimum_required(VERSION 3.2)

set(THIS_PROJECT 9.06_Priority_queues_for_index_items)
project(${THIS_PROJECT})

find_path(TREE_HEADER NAMES Tree.h PATHS "${CMAKE_FRAMEWORK_PATH}../../../")

include_directories(${TREE_HEADER})

add_executable(ex_9_13 ex_9_13.cpp)
add_executable(ex_9_14 ex_9_14.cpp)
add_executable(ex_9_16 ex_9_16.cpp)

include_directories(${THIS_PROJECT} PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()