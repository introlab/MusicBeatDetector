cmake_minimum_required(VERSION 2.6.4)

project(Utils)

set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(../3rdParty/armadillo-code/include)
include_directories(../3rdParty/fftw/build/include)
include_directories(include)

file(GLOB_RECURSE
    source_files
    src/*
    include/*)

add_library(Utils
    STATIC
    ${source_files})

target_link_libraries(Utils
        ${openblas_LIBRARY}
        ${fftw_LIBRARY}
        gfortran)

set_property(TARGET Utils PROPERTY CXX_STANDARD 14)
add_dependencies(Utils fftw openblas)

assign_source_group(${source_files})

if (MUSIC_BEAT_DETECTOR_ENABLE_TESTS)
    add_subdirectory(test)
endif()
