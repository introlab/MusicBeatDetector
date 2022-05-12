cmake_minimum_required(VERSION 2.6.4)

project(MusicBeatDetectorTests)

find_package(CUDA 9.0 QUIET)

set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(../../3rdParty/googletest/googletest/include)
include_directories(../../3rdParty/googletest/googlemock/include)
include_directories(../../3rdParty/armadillo-code/include)
include_directories(../../3rdParty/fftw/build/include)
include_directories(../../Utils/include)
include_directories(../include)
include_directories(include)


file(GLOB_RECURSE
        source_files
        src/*
        include/*)

add_executable(MusicBeatDetectorTests
        ${source_files})

target_link_libraries(MusicBeatDetectorTests
        MusicBeatDetector
        ${openblas_LIBRARY}
        ${fftw_LIBRARY}
        gtest
        gmock)

set_property(TARGET MusicBeatDetectorTests PROPERTY CXX_STANDARD 14)

assign_source_group(${source_files})

add_custom_command(TARGET MusicBeatDetectorTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:MusicBeatDetectorTests>/resources)
