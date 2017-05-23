# SK6812viaSPI
Drive SK6812 Neopixel Clones Using the SPI Data PIN
HIGHLY recomend using pixel 0 as a NULL pixel to boost 3.3v to 5v for all 3.3v Boards

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
