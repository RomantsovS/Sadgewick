cmake_minimum_required(VERSION 3.2)

set(THIS_PROJECT sort)
project(${THIS_PROJECT})

add_executable(sort main.cpp)

include_directories("${CMAKE_BINARY_DIR}")
include_directories("${CMAKE_BINARY_DIR}/../../")

if (MSVC)
    target_compile_options(${THIS_PROJECT} PUBLIC /W3 /WX)
else()
    target_compile_options(${THIS_PROJECT} PUBLIC -Wall -Wextra -pedantic -Werror)
endif()