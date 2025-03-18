cmake_minimum_required(VERSION 3.21...3.24)
include(${CMAKE_SOURCE_DIR}/cmake/load_third_party_deps.cmake)

add_runtime_enV5("v5.6.2")

project(enV5-application C CXX ASM)

eai_runtime_init()

add_unity()
add_ctest()

if (BUILDING_FOR_ELASTIC_NODE)
    message(NOTICE "INFO: Building for enV5 hardware (Type: ${CMAKE_BUILD_TYPE})")

    # add your own hardware tests
    add_subdirectory(test/hardware)

    # add your own main target
    add_subdirectory(src)
else ()
    message(NOTICE "INFO: Building for local machine")

    # add custom libraries
    add_subdirectory(src/example-lib)

    # add your own unit-tests
    add_subdirectory(test/unit)
endif ()

if (BUILDING_FOR_ELASTIC_NODE AND NOT TARGET tinyusb_device)
    message(WARNING "not building project, because tinyusb not initialized")
endif ()
