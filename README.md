# SK6812viaSPI
This repo contains basic driver code in C++ & Arduino C++ that allows you to drive SK6812, WS2812, WS2812B/Neopixels using the SPI port. Only the MOSI(DATA) pin of the SPI port is required. Below are the platforms that this has been tested on.
HIGHLY recomend using pixel 0 as a NULL pixel to boost 3.3v to 5v for all 3.3v boards or an equivelent high speed Voltage Level Shifter.

# ESP8622
YES

# Raspberry Pi via BCM2835 libarry 
YES but NO. SPI Transfers "can and will" be interupted by the OS, as your program runs in userspace so this will probbaly never work

# Raspberry Pi via SPIDEV
YES...Still working on this

# NanoPi Neo Air
YES

# STM32F103C(bluepill)
YES  
