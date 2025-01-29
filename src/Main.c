#define SOURCE_FILE "MAIN"

#include "hardware/watchdog.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"

#include "Common.h"
#include "EnV5HwController.h"
#include "FreeRtosTaskWrapper.h"

_Noreturn void ledTask(void) {
    while (true) {
        env5HwControllerLedsAllOn();
        freeRtosTaskWrapperTaskSleep(2000);

        env5HwControllerLedsAllOff();
        freeRtosTaskWrapperTaskSleep(2000);
        // or do whatever you want ...
    }
}

_Noreturn void dataTask(void) {
    while (true) {
        PRINT("Show ME!");
        freeRtosTaskWrapperTaskSleep(1000);
        // or do whatever you want ...
    }
}

_Noreturn void enterBootModeTask(void) {
    watchdog_enable(2000, 1); // enables watchdog to check for reboots

    while (true) {
        // Watchdog update needs to be performed frequent, otherwise the device will crash
        watchdog_update();
        PRINT_DEBUG("watchdog updated");
        freeRtosTaskWrapperTaskSleep(1000);
    }
}

void initializeHardware(void) {
    env5HwControllerInit();

    // First check if we crash last time -> reboot into boot rom mode
    if (watchdog_enable_caused_reboot()) {
        reset_usb_boot(0, 0);
    }

    stdio_init_all();
    while ((!stdio_usb_connected())) {
        // waits for usb connection, REMOVE to continue without waiting for connection
    }
}

int main() {
    initializeHardware();

    freeRtosTaskWrapperRegisterTask(enterBootModeTask, "watchdog-task", 0, FREERTOS_CORE_0);
    freeRtosTaskWrapperRegisterTask(dataTask, "data-task", 0, FREERTOS_CORE_0);
    freeRtosTaskWrapperRegisterTask(ledTask, "led-task", 0, FREERTOS_CORE_1);

    freeRtosTaskWrapperStartScheduler();
}
