cmake_minimum_required(VERSION 2.6.4)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

if (WIN32)
    message(FATAL_ERROR "Windows is not supported yet.")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

    add_custom_target(openblas
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/make_openblas_unix.bash"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS)

    add_custom_target(fftw
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/make_fftw_unix.bash"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fftw)

    set(openblas_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS/libopenblas.a" CACHE INTERNAL "")
    set(fftw_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/fftw/build/lib/libfftw3f.a" CACHE INTERNAL "")
endif (WIN32)

if (MUSIC_BEAT_DETECTOR_ENABLE_TESTS)
    add_subdirectory(googletest)
endif()
