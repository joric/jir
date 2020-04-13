# IR Sender

A small ESP-12F (ESP8266)-based project for DIY IR controller

## Description

Use IRController.ino (originally from https://github.com/mdhiggins/ESP8266-HTTP-IR-Blaster) with NodeMCU and IR receiver to capture IR codes (usually RAW with length 48).

Use IRSender.ino with ESP-12F and IR LED for sending the codes.


There are a few type of IR codes I couldn't make short (32-bit NEC) codes work on my devices so I went with raw ones (long sequences of numbers) sent at 38 KHz.
They ought to be 14-bit RC5 codes (https://clearwater.com.au/code/rc5), repeated 4 times on each send.


IR receiver and transmitter modules are from 37-in-1 sensors set. 3.3V regulator module is AMS1117-based.
NodeMCU modules might be a nicer choice (built in UART and 3.3V regulator) but they're more expensive than raw ESP-12F.

**WARNING: never power ESP8266 from 5V, always use 3.3V or the module dies in a about a week (confirmed!)**


## Video

[![](http://img.youtube.com/vi/UZf-yPra764/maxresdefault.jpg)](https://youtu.be/UZf-yPra764)

## Pictures

IR Sender (ESP12F-based)
![](https://i.imgur.com/cuKyaiH.jpg)

IR Receiver (NodeMCU-based)
![](https://i.imgur.com/2mgzBxz.jpg)

Fan (the black box is Hi-Link 5V PSU), built in condenser PSU is only 15 mA, ESP8266 needs 300 mA
![](https://i.imgur.com/v785Rjy.jpg)

IR Sender Web Interface
![](https://i.imgur.com/6EhBSfD.jpg)

## References

* https://www.techdesign.be/projects/011/011_waves.htm
* https://clearwater.com.au/code/rc5

