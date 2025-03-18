#include "EnV5HwConfiguration.h"
#include "EnV5HwController.h"
#include "Flash.h"
#include "UsbProtocolBase.h"
#include "UsbProtocolCustomCommands.h"

#include "CException.h"
#include "hardware/spi.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

spiConfiguration_t flashSpi = {
    .spiInstance = FLASH_SPI_MODULE,
    .sckPin = FLASH_SPI_CLOCK,
    .misoPin = FLASH_SPI_MISO,
    .mosiPin = FLASH_SPI_MOSI,
    .csPin = FLASH_SPI_CS,
    .baudrate = FLASH_SPI_BAUDRATE,
};

flashConfiguration_t flashConfig = {
    .spiConfiguration = &flashSpi,
};

usbProtocolErrorCodes_t readByteForProtocol(uint8_t *readBuffer, size_t numOfBytes) {
    for (size_t index = 0; index < numOfBytes; index++) {
        readBuffer[index] = stdio_getchar();
    }
    return USB_PROTOCOL_OKAY;
}

usbProtocolErrorCodes_t sendBytesForProtocol(uint8_t *sendBuffer, size_t numOfBytes) {
    for (size_t index = 0; index < numOfBytes; index++) {
        stdio_putchar_raw(sendBuffer[index]);
    }
    return USB_PROTOCOL_OKAY;
}

void startExperiment(__attribute((unused)) const uint8_t *payload,
                     __attribute((unused)) size_t payloadLength) {
    env5HwControllerFpgaPowersOn();
}

void initHardware() {
    env5HwControllerInit();

    stdio_usb_init();
    while (!stdio_usb_connected()) {
        // wait for serial connection
    }

    flashInit(&flashConfig);
    usbProtocolInit(readByteForProtocol, sendBytesForProtocol, &flashConfig);
    usbProtocolRegisterCommand(241, startExperiment);
}

_Noreturn void runExperiment(void) {
    while (true) {
        CEXCEPTION_T exception;
        Try {
            usbProtocolReceiveBuffer received = usbProtocolWaitForCommand();
            usbProtocolHandleCommand(received);
        }
        Catch(exception) {
            env5HwControllerLedsAllOn();
            sleep_ms(1000);
            env5HwControllerLedsAllOff();
        }
    }
}

int main(void) {
    initHardware();
    runExperiment();
}

