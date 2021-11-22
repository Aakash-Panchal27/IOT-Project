#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include "MQ135.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
DHT dht(A0, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  // DHT11 (humidity and temperature) sensor data
  float humidity = bme.readHumidity(); // in %
  float temperature = bme.readTemperature(); // in Celcius
  float pressure = bme.readPressure() / 100.0F; // in hPa
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); // in meters

  // MQ135 (Air quality) sensor data
  MQ135 gasSensor = MQ135(A1);
  float air_quality = gasSensor.getPPM();

  // Assign collected data to JSON Object
  data["humidity"] = humidity;
  data["temperature"] = temperature;
  data["pressure"] = pressure;
  data["altitude"] = altitude;
  data["air_quality"] = air_quality;

  //Send data to NodeMCU
  data.printTo(Serial);
  jsonBuffer.clear();

  delay(2000);
}
