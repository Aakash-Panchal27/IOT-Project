#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>
#include<SoftwareSerial.h>
#include "MQ135.h"

SoftwareSerial mySerial(D1, D2); // RX, TX Pins
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  String msg = mySerial.readStringUntil('\r');
  Serial.println(msg);
}
