cmake_minimum_required(VERSION 2.6.4)

project(UtilsTests)

set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(../../3rdParty/googletest/googletest/include)
include_directories(../../3rdParty/googletest/googlemock/include)
include_directories(../../3rdParty/armadillo-code/include)
include_directories(../../3rdParty/fftw/build/include)
include_directories(../include)
include_directories(include)

file(GLOB_RECURSE
    source_files
    src/*
    include/*)

add_executable(UtilsTests
    ${source_files})

set_property(TARGET UtilsTests PROPERTY CXX_STANDARD 14)

target_link_libraries(UtilsTests
    Utils
    ${openblas_LIBRARY}
    ${fftw_LIBRARY}
    gtest
    gmock)

assign_source_group(${source_files})
