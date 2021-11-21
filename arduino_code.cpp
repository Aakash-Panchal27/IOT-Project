#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>
#include "MQ135.h"

void setup() {
  Serial.begin(9600);
  DHT dht(7, DHT11);
  dht.begin();
  Serial.println("Program started");
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  // DHT11 (humidity and temperature) sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // MQ135 (Air quality) sensor data
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();

  // Assign collected data to JSON Object
  data["humidity"] = humidity;
  data["temperature"] = temperature;
  data["air_quality"] = air_quality;

  //Send data to NodeMCU
  data.printTo(Serial);
  jsonBuffer.clear();

  delay(2000);
}
