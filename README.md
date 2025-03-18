# elastic-ai.base-project

This repository provides a clean start for projects with the Elastic-AI Node Version 5 (enV5).
A modular hardware platform with FPGA integration.
It includes the hardware support libraries from the [elastic-ai.runtime.enV5 repository](https://github.com/es-ude/elastic-ai.runtime.enV5) as well as other required dependencies like the pico-sdk or Unity.

> [!TIP]
> More information about the Elastic-AI project can be found at the [project homepage](https://www.uni-due.de/es/elastic_ai.php).

## System Requirements

- **[devenv](https://devenv.sh/getting-started/)**
  -> Tool for reproducible development environments
- **[GCC](https://gcc.gnu.org/)** (through devenv)
  -> C Compiler
- **[ARM-None-EABI GCC](https://developer.arm.com/downloads/-/gnu-rm)** (through devenv)
  -> C Cross-Compiler for ARM
- **[CMake](https://cmake.org)** (through devenv)
  -> Build System
- **[Ninja](https://ninja-build.org/)** (through devenv)
  -> Build Tool
- **[Astral-UV](https://docs.astral.sh/uv/)** (through devenv)
  -> Python Runtime/Package Manager

## Set Up

> [!IMPORTANT]
> This Guide assumes you are using a devenv compatible OS.

### Get the Source Code

At first, you have to download the source code from GitHub.
This can be archived by running

```bash
git clone https://github.com/es-ude/elastic-ai.runtime.enV5.git enV5  # Download the Repository
cd enV5                                                               # Move inside the repository
```

in your shell.

### Setup devenv

1. At first you have to install devenv.
   This can be archived by following their instructions in their [Getting-Started-Guide](https://devenv.sh/getting-started/).
2. Install [direnv](https://direnv.net/), to automatically load the development environment provided by devenv.

#### Python Environment [OPTIONAL]

> [!NOTE]
> The Python environment is only required if you want to use the provided python utilities to interact with the enV5 Node.

To minimize the potential corruption of your system we recommend installing the dependencies inside
a [virtual environment](https://python.land/virtual-environments/virtualenv#How_to_create_a_Python_venv).
The python environment can be created and prepared by running:

```bash
uv venv .venv              # create a virtual python environment under `.venv/`
uv sync --all-groups       # install all python dependencies
```

### Compile the Source Code

> [!IMPORTANT]
> You have to adjust the network/mqtt broker credentials in the [NetworkConfig.c](NetworkConfig.c)!

> [!NOTE]
> This project is based on CMake.

### enV5 Node Execution

The hardware test executables for the enV5 Node can be found under [build/env5_rev2](build/env5_rev2/test/hardware)
or [build/env5_rev2_debug](build/env5_rev2_debug/test/hardware).

The `*.uf2` files to flash the pico can then be found under their respective subfolders.

### Flash the enV5

1. Press and hold `MCU BOOT` on the enV5 Node
2. Press `MCU RST` on the enV5 Node
3. Release `MCU BOOT`
4. Copy the `*.uf2` File to the RPI-RP2 device
    * Via the USB device through your file manager
    * Via the command line by executing `sudo cp <file>.uf2 /dev/sdX`

### Get Output from the enV5 Node

To receive output from the enV5 you have to connect the enV5 to your local machine.
This can be accomplished by connecting the USB-C port of the enV5 with a USB port of your local machine.

Once the enV5 is connected to your computer, you can read the debug output from the device with a serial port reader
like screen, minicom or [putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

We recommend using minicom as it is the most versatile of the aforementioned tools.
You can receive the output of the device by executing

> [!IMPORTANT]
> The serial port differs depending on the host machine!
> It can be found via `ls /dev/tty*` (Linux) or `ls /dev/tty.*` (macOS) from the terminal.

```bash
minicom
-o \             #  Disable modem initialisation
-w \             # Enable line wrap
-b 115200 \      # Set the baud rate to 115200
-D /dev/ttyACM0  # Define the serial port to read
```

in your shell.

> [!CAUTION]
> If you can’t receive any output from the enV5 the problem is possibly caused by a bug in the source code.
> If the serial output is not initialized properly (see integration tests), the enV5 is not able to send the output to
> your device!

## External Dependencies

> [!IMPORTANT]
> These dependencies will automatically be downloaded and initialized by CMake!

Following external dependencies are used by this project:

* [es-ude/elastic-ai.runtime.enV5](https://github.com/es-ude/elastic-ai.runtime.enV5)
* [es-ude/elastic-ai.runtime.c](https://github.com/es-ude/elastic-ai.runtime.c)
* [raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk)
* [FreeTROS/FreeRTOS-Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel)
* [ThrowTheSwitch/CException](https://github.com/ThrowTheSwitch/CException)
* [ThrowTheSwitch/Unity](https://github.com/ThrowTheSwitch/Unity)

* [es-ude/elastic-ai.runtime.c](https://github.com/es-ude/elastic-ai.runtime.c)

## Project structure

This project contains various folders:

|                                 Folder | Description                                         |
|---------------------------------------:|:----------------------------------------------------|
|                         [build](build) | contains all CMake generated build scripts          |
| [elasticai/baseprj](elasticai/baseprj) | Python files, e.g. usb-protocol scripts             |
|                             [src](src) | contains _Main.c_, helpers and your own source code |
|       [test/hardware/](test/hardware/) | contains your own hardware tests                    |
|                 [test/unit](test/unit) | contains your own unit tests                        |

## Troubleshooting

* To generate a clean CMake Build without deleting and reinitializing the build directory run
  `cmake --build <build_dir> --target clean`.
* If the device doesn’t connect to the wifi or mqtt broker make sure that you set up the correct
  credentials! ([NetworkConfig.c](NetworkConfig.c))

## Glossary

|                   Term |        Scope        | Description                                                                                          |
|-----------------------:|:-------------------:|:-----------------------------------------------------------------------------------------------------|
|                   enV5 |          –          | Hardware with the MCU, Flash, FPGA, …                                                                |
|                  Flash |          –          | Flash storage on the board                                                                           |
|                    HAL |          –          | Hardware Abstraction Layer   Libraries to bundle direct hardware dependencies   (uart, spi, gpio, …) |
| Config / Configuration |  FPGA, Middleware   | bin file used to configure the FPGA                                                                  |
|               FreeRTOS |       Network       | Open Source Real Time Operating System   Used to emulate Threads                                     |
|            ESP32 / ESP |       Network       | WiFi Module from espressif                                                                           |
|            AT Commands | Network, MQTT, HTTP | String based command set to control the ESP32 WiFi module                                            |
|                 Broker |    MQTT, Network    | MQTT User implementation   used to publish and subscribe to topics                                   |

## Further Reading

* [enV5 README](https://github.com/es-ude/elastic-ai.runtime.enV5)
