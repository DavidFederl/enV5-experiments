# add own libraries
add_subdirectory(example-lib)

# add your own executable
add_executable(experiment
        ${CMAKE_CURRENT_LIST_DIR}/experiment.c)
target_link_libraries(experiment
        Common
        EnV5HwConfiguration
        EnV5HwController
        Flash
        UsbProtocol

        CException

        Pico::pico_stdlib
        Pico::pico_stdio_usb
        Pico::pico_time
        Pico::hardware_spi
)
create_enV5_executable(experiment)
