cmake_minimum_required(VERSION 3.2)

set(THIS_PROJECT 9.04_Heapsort)
project(${THIS_PROJECT})

add_executable(ex_9_7 ex_9_7.cpp)

include_directories(${THIS_PROJECT} PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()