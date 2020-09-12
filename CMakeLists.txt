#############################################################################################
# configuration

cmake_minimum_required(VERSION 3.17)

set(project CosmoPort)

cmake_policy(SET CMP0048 NEW)
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)
set(CMAKE_PROJECT_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}")
PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

else()
    # stack track
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic"  CACHE STRING "compile flags" FORCE)
endif()

option(DEV_MODE "developer mode" OFF)

option(CONAN_EXPERIMENTAL_INCLUDE "CONAN EXPERIMENT INCLUDE" ON)

if (DEV_MODE)
    enable_testing()
endif ()

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
            #-Werror

            -Wall
            -Wextra
            -Wpedantic

            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wenum-compare
            -Wfloat-equal
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wsign-conversion
            -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()


# configuration
#############################################################################################
#clang format

include(cmake/clang-format.cmake)

#clang format
#############################################################################################
#conan

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if (CONAN_EXPERIMENTAL_INCLUDE)
    set(CONAN_SYSTEM_INCLUDES "On")
endif ()

conan_cmake_run(
        CONANFILE conanfile.txt
        BASIC_SETUP
        BUILD missing
        NO_OUTPUT_DIRS
)

# conan
#############################################################################################
# ccahe

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache: ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_FOUND})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_FOUND})
    set(ENV{CCACHE_COMMENTS} "1")
endif(CCACHE_FOUND)

# ccahe
#############################################################################################

add_subdirectory(components)
add_subdirectory(services)
add_subdirectory(apps)