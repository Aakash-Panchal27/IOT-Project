#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "MQ135.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

String data;

void setup() {
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  delay(1000);
}

void loop() {
  float humidity = bme.readHumidity(); // in %
  float temperature = bme.readTemperature(); // in Celcius
  float pressure = bme.readPressure() / 100.0F; // in hPa
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); // in meters

  // MQ135 (Air quality) sensor data
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();

  data = String(humidity) + String('+') + String(temperature) + String('+') +
      String(pressure) + String('+') + String(altitude) + String('+') + String(air_quality);

  Serial.println(data);
  delay(80000);
}
