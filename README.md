# Debug Arduino Zero with ST-Link V2

## Overview
 
Arduino Zero has an Atmel’s SAMD21 MCU with SWD debug support. The cheapest SWD debugger I know is a non-official ST-Link V2. It looks like a thumb drive with a 10-pin IDE on its end, and you can get it for around $2 from eBay or AliExpress, etc.

Arduino IDE doesn't support debugging when I write this. But the Boards Manager will download all necessary debug files when you install "Arduino SAMD Boards (32-bit ARM Cortex-M0+)". This tutorial will show you how you can set up debug environment in Visual Studio Code, a cross-platform free IDE with Arduino Plugin.

This tutorial is using Mac OS as an example. But I'll explain every detail to help you understand and use it on other platforms.  

## Hardware I used

![front img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/ArduinoSTLinkFront.jpg)

![back img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/ArduinoSTLinkBack.jpg)

I used an "Adafruit Feather M0 Basic Proto", soldered swdio and swclk pads on the back, 3.3V and GND to a connector. Then I connect these 4 pins to an ST-Link V2 with female wires. 

## Step 1, get Blink example working

![Blink img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/blinkExample.png)

I'll skip details on how to install board support, select board and upload examples. There are tons of tutorial you can follow. As long as you can upload a Blink example to Arduino Zero, it shows your Arduino, Boards manager, driver, Arduino Zero, are all working properly.

## Step 2, check if all OpenOCD files are ready

In order to debug Arduino Zero, you need 2 tools (comes with Arduino SAMD Boards):

OpenOCD: It connects to debugging hardware and talk to Arduino's debug interface. Then it will open a network port for other debugger software to connect. OpenOCD is doing all low-level interfacing job.

GDB: It is a debugger tool that can load ELF files from GCC compiler and convert human-readable variables and breakpoints into physical memory address on Arduino. 

All these tools should be in ~/Library/Arduino15/packages/arduino/tools/ 

You can open finder to double check if they are installed.

![OpenOCD](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/openOcdLocation.png)

Depending on your tool version, OpenOCD should be in somewhere like: 

~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd

![script folder](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/scriptsLocation.png)

Depending on your tool version, scripts for OpenOCD should be in somewhere like: 

~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts

![GDB](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/gdbLocation.png)

Depending on your tool version, GDB should be in somewhere like: 

~/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gdb

## Step 3, test whether OpenOCD and GDB is functional with terminal

**Here is a tricky part.** For some reason, the Arduino zero's ID is different from the one in the OpenOCD target. Also, with a bootloader, we don't want to have debugger change the flash content. So I copied at91samdXX.cfg to at91samdXXZero.cfg in this repo to solve the issues

Open a terminal window and paste following commands. If your files are located in a different folder from mine, edit the path accordingly. Always change the username to yours.

```
/Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/interface/stlink-v2.cfg -f /Users/sundeqing/Documents/Github/Debug-Arduino-Zero-with-ST-Link-V2/at91samdXXZero.cfg -s /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts
``` 

The command is absurdly long because there is a path with everything. Here I will explain what it means:

The openocd command works in this way:

openocd -f *config\_file\_for\_debugger* -f *config\_file\_for\_board\_or\_CPU* -s *dir\_to\_search\_for\_config\_files\_and\_scripts*


If everthing works well, you should see it working:

![openocd working](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/openOcdWorking.png)

Now we keep it running, open another terminal window and type


```
/Users/sundeqing/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gdb

```

Then you type

```
target remote localhost:3333
monitor reset halt
continue
```

The first command let GDB should connect to OpenOCD.

The second one resets and halts CPU. Arduino should stop working and LED should be OFF.

The third one resumes Arduino to work. You should see LED blinking again.

![gdb working](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/gdbWorking.png)

If everything works so far, close all terminal windows and we are ready to setup VScode.

## Step 4, setup VScode

First download VScode from <https://code.visualstudio.com/>

![download VScode](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/downloadVScode.png)

Then you install Arduino extension. Click reload after you finish install.

![installArduino](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeInstallArduino.png)

Save your Arduino Sketch somewhere, and open it in VScode with "Open Folder".

![installArduino](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeOpenFolder.png)

Then you set Board and Port, just the same ones to your settings in Step 1.

![set board and port](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeSetBoardPort.png)

Press "Option+Command+U", VScode should compile and upload your code.

![set board and port](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeUpload.png)

You can include <Arduino.h> in your arduino sketch to fix error marks under Arduino functions. 

![Add include](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeInclude.png)

Also, you can use "View" -> "Command Palette" to see all Arduino commands.

## Step 5, setup debugging in VScode

Goto "Debug" view and add configuration, add Arduino one.

![Add config](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeAddConfig.png)

You will have a default configuration, no need to add more.

![Default config](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeDefaultConfig.png)

From here, you want to edit "miDebuggerPath", "debugServerPath" and "debugServerArgs". Use ones you tested in Step 3. OpenOCD is your debugServer, GDB is your debugger.

![edited path](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeEdited.png)

Now, you go back you code, add some variable (so you can see it) and upload code again before we debug it. You can also add breakpoints.

![edited code](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeFinalCode.png)

Press F5 and happy debugging.

![edited code](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/vscodeDebugging.png)



