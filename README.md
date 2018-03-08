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

##Step 3, test whether OpenOCD and GDB is functional with terminal

Open a terminal window and paste following commands. If your files are located in a different folder from mine, edit the path accordingly.

```
~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd -f ~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/interface/stlink-v2.cfg -c "set CPUTAPID 0x0bc11477" -f ~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/board/arduino_zero.cfg -s ~/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts
``` 

The command is absurdly long because there is a path with everything. Here I will explain what it means:

The openocd command works in this way:

openocd -f *config\_file\_for\_debugger* -c *command\_to\_set\_CPUID* -f *config\_file\_for\_board\_or\_CPU* -s *dir\_to\_search\_for\_config\_files\_and\_scripts*

The reason why I put a command "set CPUTAPID 0x0bc11477", is that I got an id mismatch error without this command. So I used this command to override ID in config files.

If everthing works well, you should see it working:

![openocd working](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/openOcdWorking.png)

Now we keep it running, open another terminal window and type


```
~/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gdb

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





