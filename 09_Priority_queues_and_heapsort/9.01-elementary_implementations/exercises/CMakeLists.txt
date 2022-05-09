cmake_minimum_required(VERSION 3.2)

set(THIS_PROJECT 9.01-elementary_implementations)
project(${THIS_PROJECT})

add_executable(ex_9_7 ex_9_7.cpp)
add_executable(ex_9_8 ex_9_8.cpp)
add_executable(ex_9_9 ex_9_9.cpp)
add_executable(ex_9_13 ex_9_13.cpp)
add_executable(ex_9_14 ex_9_14.cpp)

find_path(LIST_PATH NAMES List.h PATHS "${CMAKE_FRAMEWORK_PATH}../../../")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${LIST_PATH})

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()