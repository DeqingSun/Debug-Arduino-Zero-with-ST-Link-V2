# Debug Arduino Zero with ST-Link V2

##Overview
 
Arduino Zero has an Atmel’s SAMD21 MCU with SWD debug support. The cheapest SWD debugger I know is a non-official ST-Link V2. It looks like a thumb drive with a 10-pin IDE on its end, and you can get it for around $2 from eBay or AliExpress, etc.

Arduino IDE doesn't support debugging when I write this. But the Boards Manager will download all necessary debug files when you install "Arduino SAMD Boards (32-bit ARM Cortex-M0+)". This tutorial will show you how you can set up debug environment in Visual Studio Code, a cross-platform free IDE with Arduino Plugin.

This tutorial is using Mac OS as an example. But I'll explain every detail to help you understand and use it on other platforms.  

##Hardware I used

![front img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/ArduinoSTLinkFront.jpg)

![back img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/ArduinoSTLinkBack.jpg)

I used an "Adafruit Feather M0 Basic Proto", soldered swdio and swclk pads on the back, 3.3V and GND to a connector. Then I connect these 4 pins to an ST-Link V2 with female wires. 

##Step 1, get Blink example working

![Blink img](https://github.com/DeqingSun/Debug-Arduino-Zero-with-ST-Link-V2/raw/master/img/blinkExample.png)

I'll skip details on how to install board support, select board and upload examples. There are tons of tutorial you can follow. As long as you can upload a Blink example to Arduino Zero, it shows your Arduino, Boards manager, driver, Arduino Zero, are all working properly.

##Step 2, check if all OpenOCD files are ready

In order to debug Arduino Zero, you need 2 tools (comes with Arduino SAMD Boards):

OpenOCD: It connects to debugging hardware and talk to Arduino's debug interface. Then it will open a network port for other debugger software to connect. OpenOCD is doing all low-level interfacing job.

GDB: It is a debugger tool that can load ELF files from GCC compiler and convert human-readable variables and breakpoints into physical memory address on Arduino. 

All these tools should be in ~/Library/Arduino15/packages/arduino/tools/ 

You can open finder to double check if they are installed.








/Users/sundeqing/Library/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gdb

STlink:

/Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/interface/stlink-v2.cfg -s /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/target/at91samdXXCOPY.cfg 

/Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/interface/stlink-v2.cfg -c "set CPUTAPID 0x0bc11477" -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/board/arduino_zero.cfg -s /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts


JLINK:

/Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/bin/openocd -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/interface/jlink.cfg  -c "transport select swd" -s /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts -f /Users/sundeqing/Library/Arduino15/packages/arduino/tools/openocd/0.9.0-arduino6-static/share/openocd/scripts/target/at91samdXXCOPY.cfg 

