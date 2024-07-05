cmake_minimum_required(VERSION 3.5)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

if (WIN32)
    message(FATAL_ERROR "Windows is not supported yet.")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

    execute_process(
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/make_openblas_unix.bash"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS
    )

    execute_process(
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/make_fftw_unix.bash"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fftw
    )

    add_library(
        MusicBeatDetector_openblas
        STATIC
        IMPORTED
        GLOBAL
    )

    set_target_properties(
        MusicBeatDetector_openblas
        PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS/libopenblas.a"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS/libopenblas.a"
    )

    add_library(
        MusicBeatDetector_fftw
        STATIC
        IMPORTED
        GLOBAL
    )

    set_target_properties(
        MusicBeatDetector_fftw
        PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/fftw/build/lib/libfftw3f.a"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/fftw/build/lib/libfftw3f.a"
    )
endif (WIN32)

if (MUSIC_BEAT_DETECTOR_ENABLE_TESTS)
    add_subdirectory(googletest)
endif()
