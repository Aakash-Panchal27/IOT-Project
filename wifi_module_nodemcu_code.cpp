#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

// Wifi settings
char ssid[] = "Kamlesh Panchal"; // SSID
char pass[] = "Jayambe19"; // Passowrd
unsigned long Channel_ID = 1580319; // Your Channel ID
const char * myWriteAPIKey = "0476RK7UA3KRIY2S"; //Your write API key

WiFiClient client;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  connect_to_internet();
  while (!Serial) continue;
}

String str;

void loop() {
  if (nodemcu.available()) {
    str = nodemcu.readString();

    int start = 0, end = 0;
    end = str.indexOf('+', start);
    float humidity = str.substring(start, end).toFloat();

    start = end + 1;
    end = str.indexOf('+', start);
    float temperature = str.substring(start, end).toFloat();

    start = end + 1;
    end = str.indexOf('+', start);
    float pressure = str.substring(start, end).toFloat();

    start = end + 1;
    end = str.indexOf('+', start);
    float altitude = str.substring(start, end).toFloat();

    start = end + 1;
    float air_quality = str.substring(start).toFloat();

    ThingSpeak.writeField(Channel_ID, 1, humidity, myWriteAPIKey);
    delay(5000);
    ThingSpeak.writeField(Channel_ID, 2, temperature, myWriteAPIKey);
    delay(5000);
    ThingSpeak.writeField(Channel_ID, 3, pressure, myWriteAPIKey);
    delay(5000);
    ThingSpeak.writeField(Channel_ID, 4, altitude, myWriteAPIKey);
    delay(5000);
    ThingSpeak.writeField(Channel_ID, 5, air_quality, myWriteAPIKey);
    delay(5000);
  }
}

void connect_to_internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
  }
}
