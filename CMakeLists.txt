cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(lab09)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS thread system filesystem program_options)
find_package(Boost CONFIG REQUIRED system thread filesystem program_options)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(gumbo)
find_package(gumbo CONFIG REQUIRED)

find_package(Threads)

add_library(libimage_parser
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ImageParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/PageDownloader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Page.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/LinkData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ImageParserData.cpp
)

target_include_directories(libimage_parser
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(libimage_parser
        PUBLIC
        Boost::system
        Boost::filesystem
        Boost::thread
        PRIVATE Threads::Threads
        OpenSSL::SSL OpenSSL::Crypto
        gumbo::gumbo
        Boost::boost
)

add_executable(image_parser
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
)

target_link_libraries(image_parser
        PRIVATE libimage_parser
        Boost::program_options
)

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

target_link_libraries(tests
        PRIVATE GTest::gtest_main libimage_parser
)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if(BUILD_COVERAGE)
    function(ENABLE_PROJECT_COVERAGE PROJECT)
        target_compile_options(${PROJECT} PRIVATE --coverage)
        target_link_libraries(${PROJECT} PRIVATE --coverage)
        add_coverage(${PROJECT})
    endfunction()

    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    find_package(codecov)
    enable_project_coverage(libimage_parser)
    enable_project_coverage(image_parser)
    enable_project_coverage(tests)
    list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
    coverage_evaluate()
endif()
