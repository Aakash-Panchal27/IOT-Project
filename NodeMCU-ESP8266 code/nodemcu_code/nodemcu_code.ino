/*
This is the code for WiFi module ESP8266 NodeMCU.

Basic code flow is as below:

First of all, Nodemcu ESP8266 WiFi module receives the data from Arduino's Tx pin,
and one single string is received. Now, this string is parsed using built-in String 
class function and '+' character that we have added while concatenating the parameter values.

Finally, after parsing all parameter values, we can send it to the thingspeak.com cloud using
'writeField' function by providing required parameters: Field Id, Channel Id, write API key and
parameter value.

Note that we already created a channel in ThingSpeak.com cloud, and we did set up as per our
project requirements.
*/


#include <SoftwareSerial.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// D6 = Rx & D5 = Tx
// That transmitted data from Tx pin of Arduino will be received in D6 pin of Nodemcu WiFi module.
SoftwareSerial nodemcu(D6, D5);

// Wifi settings
char ssid[] = "Kamlesh Panchal"; // SSID
char pass[] = "Jayambe19"; // Passowrd
unsigned long Channel_ID = 1580319; // Channel ID
const char * myWriteAPIKey = "0476RK7UA3KRIY2S"; // Write API key

WiFiClient client;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);

  // Set general wifi mode in usage: WIFI_STA.
  WiFi.mode(WIFI_STA);

  // Pass WiFiClient to ThingSpeak.begin() method, which will allow us to successfully
  // send the data to thingspeak.com cloud. See `ThingSpeak.writeField` function below in `loop` function.
  ThingSpeak.begin(client);

  // Check this function at the end of this code.
  // It is used to begin connection to internet using WiFi.
  connect_to_internet();
}

String str;

void loop() {
  if (nodemcu.available()) {
    str = nodemcu.readString();
    if((str[0] >= '0' and str[0] <= '9')) {
      
      // Parsing parameters one by one.
      // Using functions provided by String built-in class in Arduino IDE, to parse data using '+' character
      // that have been used while creating a single string of all parameter values at Arduino.
      int start = 0, end = 0;
      end = str.indexOf('+', start);
      float humidity = str.substring(start, end).toFloat();
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println("%");
  
      start = end + 1;
      end = str.indexOf('+', start);
      float temperature = str.substring(start, end).toFloat();
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println("*C");
  
      start = end + 1;
      end = str.indexOf('+', start);
      float pressure = str.substring(start, end).toFloat();
      Serial.print("Pressure: ");
      Serial.print(pressure);
      Serial.println("hPa");
  
      start = end + 1;
      end = str.indexOf('+', start);
      float altitude = str.substring(start, end).toFloat();
      Serial.print("Altitude: ");
      Serial.print(altitude);
      Serial.println("m");
  
      start = end + 1;
      float air_quality = str.substring(start).toFloat();
      Serial.print("Air Quality: ");
      Serial.print(air_quality);
      Serial.println("ppm");
  
      Serial.println("--------------------------------------");
  
      // Use functions provided by ThingSpeak.h library to write data to the channel on thingspeak.com cloud.
      ThingSpeak.writeField(Channel_ID, 1, humidity, myWriteAPIKey);

      // Here 15 seconds (15000 ms) is taken because single write update time for a channel in thingspeak.com is 15 seconds.
      delay(15000);
      
      ThingSpeak.writeField(Channel_ID, 2, temperature, myWriteAPIKey);
      delay(15000);
      
      ThingSpeak.writeField(Channel_ID, 3, pressure, myWriteAPIKey);
      delay(15000);
      
      ThingSpeak.writeField(Channel_ID, 4, altitude, myWriteAPIKey);
      delay(15000);
      
      ThingSpeak.writeField(Channel_ID, 5, air_quality, myWriteAPIKey);
      delay(15000);
    }
  }
}

// Function used to connect to internet.
void connect_to_internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    // Until successfully connected, try again and again.
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
  }
}
