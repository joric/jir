# joirc

A small ESP-12F (ESP8266)-based project for DIY IR controller

## Description

Use IRCapture for Arduino Nano with VS1838 IR receiver (from 37 in 1 set) to capture IR codes in RAW format.
Use IRSender with ESP-12F and IR LED to send the codes. Mind that ESP12-F dies from 5V in about a week so use 3.3V regulator
(e.g. AMS1117-based). NodeMCU modules are better (built in UART and 3.3V LDO) but they're a little bit expensive.

There are a lot of types of IR codes, I went with RAW ones (long sequences of timings) sent at 38 KHz. You can also capture and decode them
with [IrScrutinizer](https://github.com/bengtmartensson/IrScrutinizer/releases) and Arduino Nano
(with [GirsLite 1.0.2](https://github.com/bengtmartensson/AGirs/releases) firmware). Hook up IR receiver module to pins D5, GND and 5V, check "Use receive for capture"
in capture settings, export as Arduino or Bracketed RAW.

## Video

[![](http://img.youtube.com/vi/UZf-yPra764/maxresdefault.jpg)](https://youtu.be/UZf-yPra764)

## Pictures

* https://imgur.com/a/qzOVUFb

## Web

* https://joric.github.io/joirc

## References

* https://joric.github.io/joirc
* https://imgur.com/a/qzOVUFb
* https://www.techdesign.be/projects/011/011_waves.htm
* https://clearwater.com.au/code/rc5
* http://www.hifi-remote.com/johnsfine/DecodeIR.html
* https://github.com/probonopd/irdb
* https://github.com/bengtmartensson/IrScrutinizer
* https://github.com/bengtmartensson/AGirs
* https://github.com/probonopd/decodeir
