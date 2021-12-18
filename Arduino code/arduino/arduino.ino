/*
We are measuing five parameters:
1. Temperature
2. Humidity
3. Pressure
4. Altitude
5. Air Quality

This is the code for Arduino.

Basic code flow is as below:

Arduino reads different parameter data using sensors (MQ135 and BME280) and
sends the concatenated string of all parameter values to ESP8266 Nodemcu WiFi module.
*/

#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

String data;

void setup() {
  Serial.begin(9600);
  while (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    delay(5000);
  }
  Serial.flush();
  delay(1000);
}

void loop() {
  // Reading BME sensor data
  float humidity = bme.readHumidity(); // in %
  float temperature = bme.readTemperature(); // in Celcius
  float pressure = bme.readPressure() / 100.0F; // in hPa
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); // in meters

  // MQ135 (Air quality) sensor data
  float air_quality = analogRead(A0); // in PPM

  // Creating concatenated string consisting of all five parameter values.
  // Note that here '+' character added just to seperate different parameter values
  // This '+' character will be used in the Nodemcu code to parse the data and get all parameter values seperately.
  data = String(humidity) + String('+') + String(temperature) + String('+') +
      String(pressure) + String('+') + String(altitude) + String('+') + String(air_quality);

  // This will transmit 'data' string from the Tx pin (pin no: 1) of Arduino.
  Serial.println(data);
  delay(80000);
}
