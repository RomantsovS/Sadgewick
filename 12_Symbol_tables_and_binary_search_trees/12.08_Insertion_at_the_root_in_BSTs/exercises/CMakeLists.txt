cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 12.08_Insertion_at_the_root_in_BSTs)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

add_executable(ex_12_73 ex_12_73.cpp)
add_executable(ex_12_76 ex_12_76.cpp)

set(
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include_directories( PRIVATE "${CMAKE_BINARY_DIR}")