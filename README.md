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

## IR Codes

There are a lot of formats, autodetection and generation of those formats is pretty complicated.
You could try looking into [IrpTransmogrifier](https://github.com/bengtmartensson/IrpTransmogrifier) code
(used in [IrScrutinizer](https://github.com/bengtmartensson/IrScrutinizer)).
This is probably the best detector and generator that reads IRP format notation from the XML definition file
([IrpProtocols.xml](https://github.com/bengtmartensson/IrpTransmogrifier/blob/master/src/main/resources/IrpProtocols.xml)),
so it's data-driven and not hardcoded as, for example [decodeir](https://github.com/probonopd/decodeir).

### Raw format

RAW format is pretty simple, it's just a comma-separated sequence of timings (with alternating amplitude) e.g:

`1330,438,1258,440,410,1288,1260,438,1258,440,384,1312,386,1312,412,1286,386,1312,386,1312,1260,440,384,8106`

Timings also could be explicitly written with alternating signs, '+' means high, '-' means low (order is always the same):

`+1330 -438 +1258 -440 +410 -1288 +1260 -438 +1258 -440 +384 -1312 +386 -1312 +412 -1286 +386 -1312 +386 -1312 +1260 -440 +384 -8106`

Bits are encoded in pairs, [long,short] is 1, [short,long] is 0, e.g. [1330,438] is 1, [410,1288] is 0.
Examples above are the same 12 bits, 110110000010. For F12 signal (D:3,S:1,F:8) that means D=3, S=1, F=65 (110+1+10000010 = 011b, 1b, 01000001b),
where D is device code, S is subdevice code, F is function.

### IRP format notation

Example: **Mitsubishi {32.6k,300}<1,-3|1,-7>(D:8,F:8,1,-80)+**

* **{32.6k,300}** general: {carrier frequency, time unit, sequencing rule}
	* Carrier Frequency: Hz; e.g. 38.3k; default is 0k--no modulation
	* Time Unit: Integer that can represent durations. Suffix u (default) is microseconds, p denotes number of pulses of the carrier.
	* Sequencing Rule: lsb|msb; lsb (default) means the least significant bit of a binary form is sent first.

* **<1,-1|1,-3>** BitSpec: Rule for the translating bit sequences to duration sequences.
<ZeroPulseSeq|OnePulseSeq|TwoPulseSeq....>.
Most IR protocols use only <ZeroPulseSeq|OnePulseSeq>, and the sequence is simply OnDuration,OffDuration. Example: NEC uses <1,-1|1,-3>

* **(D:8,F:8,1,-80)+** Bitfield: D:NumberOfBits:StartingBit.
if D=47= 01000111, D:2:5 means x10xxxxx. D:2:5 = 10b = 2. ~ is the bitwise complement operator. ~D =10111000. Specifying the StartingBit is optional. D:6 is equivalent to D:6:0.
A trailing + means send one or more times. A trailing 3 means send 3 times; 3+ means at least 3 times. A trailing * means send zero or more times


#### More examples

* NEC: {38.4k,564}<1,-1|1,-3>(16,-8,D:8,S:8,F:8,~F:8,1,^108m)
* F12: {37.9k,422}<1,-3|3,-1>(D:3,S:1,F:8,-80)*

See http://www.hifi-remote.com/johnsfine/DecodeIR.html for details.

## References

* https://github.com/mdhiggins/ESP8266-HTTP-IR-Blaster
* https://www.techdesign.be/projects/011/011_waves.htm
* https://clearwater.com.au/code/rc5
* http://www.hifi-remote.com/johnsfine/DecodeIR.html
* https://github.com/probonopd/irdb
* https://github.com/bengtmartensson/IrScrutinizer
* https://github.com/bengtmartensson/AGirs
* https://github.com/probonopd/decodeir
