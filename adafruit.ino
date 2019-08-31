#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
SoftwareSerial s(D6,D5);

#define WLAN_SSID       "kanna"      //mention SSID 
#define WLAN_PASS       "12345678"      //mention Password

//////////////////////////////////////////

#define AIO_SERVER      "io.adafruit.com" // server name
#define AIO_SERVERPORT  1883

////////////////////////////////////////////
#define IO_USERNAME  "ranjithkanna"
#define IO_KEY       "c2280971d95848ac92962811ddd56344"

/////////////////////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
////////////////////////////////////
Adafruit_MQTT_Publish beforepollution = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/beforepollution");
Adafruit_MQTT_Publish afterpollution = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/afterpollution");
void MQTT_connect();
//////////////////////////////////////////
void setup()
{
  s.begin(9600);
  Serial.begin(9600);
  while (!Serial) continue;
  Serial.println(F("Adafruit MQTT demo"));
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
}
 
void loop()
{
   MQTT_connect();
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 
  if (root == JsonObject::invalid())
  {
    return;
  }
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("pollution 1  ");
  int data1=root["p1"];
  Serial.println(data1);
  Serial.print("pollution 2  ");
  int data2=root["p2"];
  Serial.println(data2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");


beforepollution.publish(data1);
afterpollution.publish(data2);

     
  
 delay(1000);
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
