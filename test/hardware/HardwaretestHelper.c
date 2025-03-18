#define SOURCE_FILE "TEST-HELPER"

#include "hardware/watchdog.h"
#include "pico/bootrom.h"
#include "pico/stdio_usb.h"

#include "EnV5HwController.h"
#include "Esp.h"
#include "FreeRtosTaskWrapper.h"
#include "HardwaretestHelper.h"
#include "MqttBroker.h"
#include "Network.h"

void connectToNetwork(void) {
    networkTryToConnectToNetworkUntilSuccessful();
}

void connectToMqttBroker(void) {
    mqttBrokerConnectToBrokerUntilSuccessful("eip://uni-due.de/es", "enV5");
}

void initializeHardwareTest(void) {
    env5HwControllerInit();

    // Did we crash last time -> reboot into boot rom mode
    if (watchdog_enable_caused_reboot()) {
        reset_usb_boot(0, 0);
    }

    stdio_init_all();
    while ((!stdio_usb_connected())) {}

    espInit(); // initialize ESP32 module

    watchdog_enable(2000, 1);
}

void _Noreturn enterBootModeTaskHardwareTest(void) {
    while (1) {
        if (getchar_timeout_us(10) == 'r' || !stdio_usb_connected()) {
            reset_usb_boot(0, 0);
        }
        watchdog_update();
        freeRtosTaskWrapperTaskSleep(1000);
    }
}
