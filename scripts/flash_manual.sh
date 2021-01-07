#!/bin/sh

 ~/.platformio/penv/bin/python ~/.platformio/packages/tool-esptoolpy/esptool.py   --chip esp32 --port "/dev/cu.usbserial-1410" --baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /Users/andrewmaule/Documents/PlatformIO/Projects/esp32-cam/.pio/build/esp32cam/bootloader.bin 0x18000 /Users/andrewmaule/Documents/PlatformIO/Projects/esp32-cam/.pio/build/esp32cam/partitions.bin 0x20000 .pio/build/esp32cam/firmware.bin
