################## hardwareTestHelper ##################
add_library(hardware-testHelper HardwaretestHelper.c)
target_link_libraries(hardware-testHelper
        Pico::pico_stdlib
        Pico::pico_stdio_usb
        EnV5HwController
        MqttBroker
        Common
        Esp
        Network
        freeRtosUtils)
target_include_directories(hardware-testHelper PUBLIC ${CMAKE_SOURCE_DIR}/src)

################## test_MQTTPublish ##################
add_executable(hardware-test_MQTTPublish HardwaretestMqttPublish.c)
target_link_libraries(hardware-test_MQTTPublish
        Pico::pico_stdlib
        Common
        RuntimeC::Protocol
        freeRtosUtils
        hardware-testHelper)
target_compile_definitions(hardware-test_MQTTPublish PRIVATE DEBUG)
create_enV5_executable(hardware-test_MQTTPublish)