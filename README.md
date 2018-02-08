# codal-mbedos

This library is a binary build of mbedos, and the necessary include files to enable it's use. This is provided here to reduce code size and complexity in the common case (as mbedos source is rather large). The repo also contains a mapping of the codal APIs onto ARM's mbed os.

## Generating Object Files

To extract binary files for a new target, follow these steps:

 - Install [mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).
 - From the command-line, import the mbedos blinky example:

```
mbed import mbed-os-example-blinky
cd mbed-os-example-blinky
```

 - compile with the GCC toolchain and your desired target target:

```
mbed compile -m nrf52_DK -t GCC_ARM
```

 - Copy the "create_codal_target.py" file from the repo into the mbed-os-example-blinky directory, and execute it.

```
python create_codal_target.py
```

 - This will create a new directory with a folder structure similar to others in this repository.
 
## FAQs
 
### Do you use the feature of the RTOS (RTX from Keil) integrated in mbed?

We run inside the main thread of the RTOS, but do not use any other RTOS features. We determine where our stack is for the fiber scheduler [here](https://github.com/lancaster-university/codal-brainpad/blob/master/inc/device_fiber.h#L33)
 
### Which version of mbed os are you using?

Because mbedos is such a large project, we find it quicker to produce a pre-compiled version of the library as a binary library formed of object files. We are currently building off of mbedos version 5.7.3 (0d24148513d5971c8141de3d859a0af0a948b47d), which you should be able to find on github (https://github.com/ARMmbed/mbed-os). 
