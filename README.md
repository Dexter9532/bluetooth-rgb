# Bluetooth-rgb

## Requierments

- https://docs.zephyrproject.org/latest/develop/getting_started/index.html
- https://learn.adafruit.com/adafruit-esp32-s3-tft-feather/overview

## Project

This project is about learning bluetooth and how to send hex data from a connected device to the EPS32 and then change the built in RGB LED to the rec

## How to use?

- Install some kind of bluetooth app that can send messages on your device, I use LightBlue.
- Build and flash:

```
west build -p always \
            -b adafruit_feather_esp32s3_tft_reverse/esp32s3/procpu  && west flash
```

- Connect and send in hex xx+xx+xx.

