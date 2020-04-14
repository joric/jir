//this sketch will capture remote control buttons on the serial monitor of the Arduino Nano
//connect IR receiver from 37 in 1 sensor kit to pin D2 (signal) and 5V/GND accordingly
//if Arduino Nano configuration doesn't work try building as Duemilanove or Diecimila

#include <IRremote.h>			//load the IRremote library

int RECV_PIN = 2;				//Set the IRreceiver on pin 2 on the Arduino
IRrecv irrecv(RECV_PIN);		//Create an instance for irrecv
decode_results results;			//Create an instance to store the collected data in

void setup() {
	Serial.begin(9600);			//start the serial monitor
	Serial.println("Ready.");	//print the line between the quotes
	irrecv.enableIRIn();		//start the reciever
}

void loop() {
	if (irrecv.decode(&results))	//this line checks if we received a signal from the IR receiver
	{
		for (int i = 1; i < results.rawlen; i++) {
			Serial.print(results.rawbuf[i]*55);
			if (i != results.rawlen-1)
				Serial.print(",");
		}
		Serial.println();
		irrecv.resume();		//receive the next value
	}
}
