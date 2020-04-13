#include <IRsend.h>
#include <ESP8266WiFi.h>

#include "config.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiServer server(80);

const uint16_t kIrLed = D2; // pin 4
IRsend irsend(kIrLed);

void setup() {

	irsend.begin();

	Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
	delay(10);

	pinMode(kIrLed, OUTPUT);
	digitalWrite(kIrLed, 0);

	// Connect to WiFi network
	WiFi.mode(WIFI_STA); //you can use different modes, also make sure to change the mode in the rewifi() function
	WiFi.begin(ssid, password);
	delay(5000); //you can change the delay. Incase of electricy cut-off, when power returns, the router takes about 15sec to make the wifi functional.
	server.begin();

	Serial.println("---");
	Serial.println("Connected.");
	Serial.println(WiFi.localIP());
}

void rewifi(){
	if(WiFi.status() != WL_CONNECTED) {
			WiFi.disconnect();
			WiFi.mode(WIFI_STA);
			WiFi.begin(ssid, password);
			delay(5000);
		}
}

void loop() {
	if(WiFi.status() != WL_CONNECTED) {
		rewifi();
		return;
	}

	delay(100);

	// Check if a client has connected
	WiFiClient client = server.available();
	if (!client) {
	return;
	}

	// Wait until the client sends some data
	while(!client.available()){
		delay(1);
	}

	// Read the first line of the request
	String request = client.readStringUntil('\r');
	client.flush();

	// Set LED according to the request
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println(""); //	do not forget this one
	client.println("<!DOCTYPE HTML>");
	client.println("<html>");
	client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	client.println("<title>IR Sender</title>");
	client.println("<h1>IR Sender</h1>");

  client.println("<form action='/'>");

  client.println("<textarea name=raw rows=4 cols=80 placeholder='comma-separated decimal values'>");
  client.println("</textarea>");

  if (request.indexOf("/?raw=") != -1) {
    const int buf_size = 1024;
    uint16_t raw[buf_size];
    
    int p1 = request.indexOf("=") + 1;
    int size = 0;    
    while (size<buf_size) {
      int p2 = request.indexOf("%", p1);
      int value = request.substring(p1, p2==-1 ? request.length() : p2).toInt();
      raw[size++] = value;
      if (p2==-1) break;
      p1 = p2 + 3; // + %2C
    }

    Serial.println(); Serial.print("sending "); Serial.print(size); Serial.println(" values");
    irsend.sendRaw(raw, size, 38);
  }

  client.println("<br><input type=submit value='Send (at 38 KHz)'>");
  client.println("</form>");
  client.println("</html>");

  delay(1);
}
