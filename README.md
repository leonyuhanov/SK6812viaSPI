# SK6812viaSPI
Drive SK6812 Neopixel Clones Using the SPI Data PIN

ESP8622: Works flawlessly.

Raspberry Pi: YES but NO. SPI Transfers "can and will" be interupted by the OS, as your program runs in userspace so this will probbaly never work

NanoPi Neo Air - Yes, need to use Pixel 0 as a NULL Driver pixel to boost 3.3v to 5 for the rest of the strip

STM32F103C(bluepill) - Yes, need to use Pixel 0 as a NULL Driver pixel to boost 3.3v to 5 for the rest of the strip
  
