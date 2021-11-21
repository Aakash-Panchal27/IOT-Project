//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// D1 = Rx & D2 = Tx
SoftwareSerial nodemcu(D1, D2);

// Wifi settings
char ssid[] = "Kamlesh Panchal"; // SSID
char pass[] = "Jayambe19"; // Passowrd
unsigned long Channel_ID = 0; // Your Channel ID
const char * myWriteAPIKey = ""; //Your write API key

WiFiClient client;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  connect_to_internet();
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");

  float humidity = data["humidity"];
  float temperature = data["temperature"];
  float air_quality = data["air_quality"];
  ThingSpeak.writeField(Channel_ID, 1, humidity, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, 2, temperature, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, 3, air_quality, myWriteAPIKey);
  delay(15000);
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
