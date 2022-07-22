cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(THIS_PROJECT 5.08_Graph_traversal)
project(${THIS_PROJECT} VERSION ${PROJECT_VESRION})

find_path(ITEM_HEADER NAMES Queue.h PATHS
"${CMAKE_FRAMEWORK_PATH}../../../")
include_directories(${ITEM_HEADER})

add_executable(ex_5_21 ex_5_21.cpp)
add_executable(ex_5_22 ex_5_22.cpp)

set_target_properties(ex_5_21 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include_directories(ex_5_21 PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    target_compile_options(ex_5_21 PRIVATE
        /W4
    )
else ()
    target_compile_options(ex_5_21 PRIVATE
        -Wall -Wextra -pedantic -Werror -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
    )
endif()