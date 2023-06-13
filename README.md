# LED Reading Light with ESP32 Devkit1 

This is a project to create a smart LED Reading Light using an ESP32 Devkit1. It will allow you to control the on/off state and brightness level of an LED strip, making it an ideal solution for a reading light in your bedroom. This README includes the steps for setting up the project, including the necessary code and hardware setup.

## Features

- On/Off control.
- Brightness control (+ and - buttons).

## Hardware Components

- ESP32 Devkit1
- LED strip
- 3 push-buttons
- Resistors
- Breadboard and wires

## Schematic

A detailed schematic of how to connect the LED strip and the push buttons to the ESP32 Devkit1 will be added here. 

## Software Requirements

- PlatformIO IDE
- ESP32 Board definitions for PlatformIO IDE
- LED Control library (recommend FastLED)

## Code

Source code files are available in the `src` directory of this repository.

## Setup Instructions

1. **Install PlatformIO IDE**: Download and install the PlatformIO IDE from [PlatformIO's official website](https://platformio.org/platformio-ide).

2. **ESP32 Board definitions**: Add ESP32 board definitions to your PlatformIO IDE. Follow [this guide](https://docs.platformio.org/en/latest/boards/espressif32/esp32dev.html) for detailed instructions.

3. **Download and Install Libraries**: Open PlatformIO IDE and navigate to PIO Home > Libraries. Search for `FastLED` and install the latest version.

4. **Load Source Code**: Clone this repository and open the PlatformIO project located in the `src` directory in PlatformIO IDE.

5. **Upload the Code**: Connect the ESP32 Devkit1 to your computer using a USB cable. Select the correct board (`esp32dev`) and port, then click on `Upload`.

## Usage Instructions

- Press the On/Off button to toggle the LED strip on or off.
- Use the + and - buttons to increase or decrease the brightness of the LED strip.

## Troubleshooting

If you encounter any problems, please check the following:

1. **Connections**: Ensure all hardware components are properly connected as per the schematic.
2. **Code Upload**: Ensure there are no errors during code upload.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [ESP32 DevKit documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)
- [FastLED library](http://fastled.io/)

Feel free to reach out if you have any questions or need further assistance in setting up this project.
