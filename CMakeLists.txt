cmake_minimum_required(VERSION 2.6.4)

if (POLICY CMP0014)
    cmake_policy(SET CMP0014 NEW)
endif (POLICY CMP0014)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(mixer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif ()

if (CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DRELEASE=1)
endif ()

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif (MSVC)

function(assign_source_group)
    foreach (_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else ()
            set(_source_rel "${_source}")
        endif ()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach ()
endfunction(assign_source_group)


set(openblas_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/OpenBLAS/libopenblas.a")
set(fftw_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/fftw/build/lib/libfftw3f.a")


add_subdirectory(3rdParty)
add_subdirectory(Utils)
add_subdirectory(MusicBeatDetector)

set_target_properties(gmock PROPERTIES FOLDER 3rdParty)
set_target_properties(gmock_main PROPERTIES FOLDER 3rdParty)
set_target_properties(gtest PROPERTIES FOLDER 3rdParty)
set_target_properties(gtest_main PROPERTIES FOLDER 3rdParty)