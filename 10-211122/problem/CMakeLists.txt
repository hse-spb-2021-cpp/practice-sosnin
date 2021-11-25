cmake_minimum_required(VERSION 3.5)
project(ex-10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")

include(conan.cmake)

conan_cmake_run(
    REQUIRES
        boost/1.71.0
    BASIC_SETUP
    CMAKE_TARGETS
    UPDATE
    OPTIONS
        boost:shared=True
        boost:fPIC=True
    BUILD
        missing
    GENERATORS
        cmake_paths
        cmake_find_package
    )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_BINARY_DIR})

find_package(boost COMPONENTS filesystem REQUIRED)

include_directories(
    ${CONAN_INCLUDE_DIRS}
    ./20-boost-dll-has
    ./03-boost-dll
    )

add_executable(01-boost-header-only
    01-boost-header-only.cpp
    )

add_executable(02-boost-link-filesystem
    02-boost-link-filesystem.cpp
    )

target_link_libraries(02-boost-link-filesystem
    PRIVATE
        Boost::filesystem
    )

add_executable(example-01
    ../examples/01.cpp
)

add_executable(example-02
    ../examples/02.cpp
)
