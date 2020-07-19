#include <ESP8266WiFi.h>

#include "config.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

WiFiServer server(80);

void setup() {
  // The starting baud rate can be changed to 19200 by holding down the Clean button
  // while powering on Roomba until you hear a sequence of descending tones
  // but you have to disconnect the battery to set it back to 115200
  // I recommend setting default 115200 for compatibility
  Serial.begin(115200);
  Serial.write(129); // 129 - Baud command
  delay(50);
  Serial.write(11); // 11 - 115200
  delay(50);

  // Connect to WiFi network
  WiFi.mode(WIFI_STA); // you can use different modes, also make sure to change
                       // the mode in the rewifi() function
  WiFi.begin(ssid, password);
  delay(5000); // you can change the delay. Incase of electricy cut-off, when
               // power returns, the router takes about 15sec to make the wifi
               // functional.
  server.begin();
}

void rewifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    delay(5000);
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
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
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //	do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, "
                 "initial-scale=1.0\">");
  client.println("<title>Roomba</title>");
  client.println("<h1>Roomba</h1>");

  client.println("<form action='/'>");

  client.println(
      "<textarea name=raw rows=4 cols=80 placeholder='comma-separated numbers "
      "to send (128-init, 131-safe, 135-clean, 134-spot, 143-dock)'>");
  client.println("</textarea>");

  if (request.indexOf("/?raw=") != -1) {
    const int buf_size = 1024;
    uint8_t raw[buf_size];

    int p1 = request.indexOf("=") + 1;
    int size = 0;
    while (size < buf_size) {
      int p2 = request.indexOf("%", p1);
      int value =
          request.substring(p1, p2 == -1 ? request.length() : p2).toInt();
      raw[size++] = value;
      if (p2 == -1)
        break;
      p1 = p2 + 3; // + %2C
    }

    for (int i = 0; i < size; i++) {
      Serial.write(raw[i]);
      delay(50);
    }
  }

  client.println("<br><input type=submit value='Send to Roomba serial'>");
  client.println("</form>");
  client.println("</html>");

  delay(1);
}
