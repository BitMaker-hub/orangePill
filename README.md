# The Orange Pill
## Description
The OrangePill is a new social mechanism to onboard, gift, transfer or sell bitcoin in a physical, safe and reusable way.

It is a real HW Orange Pill that can be used in a community as cash. It also can be the entry point for those who doesn't know anything about Bitcoin and the best, it can be used as many times you want. 

## ATTENTION! This project is still in developement and must be tested on tesnet

## How can I use it?
Receive 💊 ➡️ Create 🌱💦 ➡️ Save ₿ 🔐➡️ Give it away

Receive 🔐 💊 ➡️ Unlock 🌱 ₿ ➡️ Reboot 💊 ➡️ Repeat with others 🔄

![image](https://github.com/BitMaker-hub/orangePill/tree/master/IMAGES/OrangePill.png)


## How it works?
### PILL AS A KEYBOARD
The OrangePill works as a input HID device, it emulates keyboard strokes. Every time you push it's button sends keystrokes.
It don't need any specific app to work. Works on any device or pc, you just need to open a notepad or any text editor and press the pill button.

Posible inputs:

- One push:   Shows current status, display options and show xpub or mnemonic depending of it's state.
- Two pushes: Shows # times pill was used, public gpg of interal hw + signed message.
- Hold 5 sec: Depending of it's state > Start seed generation / Unlock seed / Reset pill
- SHAKE: During seed generation or seed unlock.


###PILL STATES

The orangePill has currently three sates.

VIRGIN: No seed present. Needs to generate entropy. 
LOCKED: Seed present. When you make one push you can only see xpub.
UNLOCKED: Seed revealed. When you make one push you can see mnemonic.

![image](https://github.com/BitMaker-hub/orangePill/tree/master/IMAGES/workflow.png))


## HW Specifictions
- ESP32S2
- LEDs WS2812B
- Button
- Accelerometer KXTJ3-1057
- ATTEC608A

![image](https://github.com/BitMaker-hub/orangePill/tree/master/IMAGES/hardware.gif))

## Libraires
- Main library -> <a href="https://www.arduino.cc/reference/en/libraries/ubitcoin/">uBitcoin</a>
- Adafruit_NeoPixel
- kxtj3-1057
- hidkeyboard