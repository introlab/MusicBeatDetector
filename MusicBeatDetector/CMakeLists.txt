cmake_minimum_required(VERSION 3.5)

project(MusicBeatDetector)

set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(../3rdParty/armadillo-code/include)
include_directories(../3rdParty/fftw/build/include)
include_directories(../Utils/include)
include_directories(include)

file(GLOB_RECURSE
        source_files
        src/*
        include/*)

add_library(MusicBeatDetector
        STATIC
        ${source_files})

target_link_libraries(MusicBeatDetector
        MusicBeatDetector_openblas
        MusicBeatDetector_fftw
        gfortran)

set_property(TARGET MusicBeatDetector PROPERTY CXX_STANDARD 14)

assign_source_group(${source_files})

if (MUSIC_BEAT_DETECTOR_ENABLE_TESTS)
    add_subdirectory(test)
endif ()
