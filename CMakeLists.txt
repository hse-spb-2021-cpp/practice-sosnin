cmake_minimum_required(VERSION 3.10)

project(lab01-examples CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/W4 /WX)
    # Do not specify /O2 because there are Debug/Release modes.
else()
    if (NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE Debug CACHE STRING "Default build type from CMakeLists.txt" FORCE)  # Add debug information
    endif (NOT CMAKE_BUILD_TYPE)

    add_compile_options(-Wall -Wextra -Werror -O2)
    if (UNIX AND NOT CMAKE_CXX_FLAGS)  # Do not add if -DCMAKE_CXX_FLAGS is passed
      add_compile_options(-fsanitize=address -fsanitize=undefined)
      add_link_options(-fsanitize=address -fsanitize=undefined)
    endif (UNIX AND NOT CMAKE_CXX_FLAGS)
endif (MSVC)

add_executable(lab02_01 lab02-examples/210913.cpp)

add_executable(lab04_01 lab04-examples/210927.cpp)

add_executable(lab05_01 lab05-examples/211004.cpp lab05-examples/lib.cpp)
target_include_directories(lab05_01 PRIVATE lab05-examples)

