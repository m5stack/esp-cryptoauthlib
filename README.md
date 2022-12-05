> <b>Effective March 6, 2023, AWS will end support for AWS IoT EduKit, a program that guided builders on how to develop simple IoT applications with AWS Partner reference hardware and tutorials. AWS IoT EduKit’s reference hardware kit is made and sold by our manufacturing partner, M5Stack Technology Co., Ltd. (https://m5stack.com/), who will continue to offer and support the kit and related software for interested customers.</b>
> 
> # ESP-CRYPTOAUTHLIB

This is a port of Microchip's [cryptoauthlib](https://github.com/MicrochipTech/cryptoauthlib) to work on the [M5Stack Core2 for AWS IoT EduKit](https://aws.amazon.com/iot/edukit/#Get_started_with_AWS_IoT_EduKit). It contains necessary build support to use cryptoauthlib with ESP-IDF as well as `esp_cryptoauthlib_utility` for configuring and provisiong ATECC608 chip integrated with the Core2 for AWS. The cryptoauthlib folder is a submodule of Microchip's [cryptoauthlib](https://github.com/MicrochipTech/cryptoauthlib). This ported library requires the [Core2 for AWS IoT EduKit board support package](https://github.com/m5stack/Core2-for-AWS-IoT-EduKit/tree/BSP-dev) (BSP) to be included for thread-safe access to the I2C bus using Rop Gonggrijp's I2C Manager, and power to the chip using the ported Mika Tuupola's AXP192 driver.

## Requirements

* Core2 for AWS IoT EduKit BSP(https://github.com/m5stack/Core2-for-AWS-IoT-EduKit/tree/BSP-dev)
* Configuration in [sdkconfig.defaults](https://github.com/aws-iot-edukit/Project_Template-Core2_for_AWS/blob/main/sdkconfig.defaults)
* Preferred [ESP-IDF](https://github.com/espressif/esp-idf) tag `release/v4.3` or newer OR use PlatformIO with [Espressif32 platform](https://github.com/platformio/platform-espressif32/) v3.3.1+.
* Environment variable `IDF_PATH` should be set

## How to use esp-cryptoauthlib with ESP-IDF
---
There are two ways to use **esp-cryptoauthlib** and the Core2 for AWS BSP in your project

1) Directly add **esp-cryptoauthlib** and the BSP as a component in your project with following three commands.

    (First change directory (cd) to your project directory)
```
    mkdir components
    cd components
```
2) Add **esp-cryptoauthlib** as an extra component in your project.

* Download **esp-cryptoauthlib** and the **Core2 for AWS BSP** with:
```
    git clone https://github.com/espressif/esp-cryptoauthlib.git --recurse-submodules
    git clone https://github.com/m5stack/Core2-for-AWS-IoT-EduKit.git --recurse-submodules
```
3) Enable the correct configurations for ESP-IDF using KConfig menu:
```
    idf.py menuconfig
```


If you have downloaded the repos without using the --recurse-submodules argument, you need to run this command in each repo:
```
git submodule update --init --recursive
```

* Include  `esp-cryptoauthlib` in `ESP-IDF` with setting `EXTRA_COMPONENT_DIRS` in CMakeLists.txt/Makefile of your project.For reference see [Optional Project Variables](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#optional-project-variables)

## How to configure and provision ATECC608 on Core2 for AWS
The python utilty `esp_cryptoauth_utility` helps to configure, generate resources as well as provision ATECC608 chip integrated with the Core2 for AWS.
For detailed instructions on how to use the utility please refer utility [README.md](esp_cryptoauth_utility/README.md)

## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This library is licensed under the MIT-0 License. See the LICENSE file.
