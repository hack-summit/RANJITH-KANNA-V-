
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include<Firebase.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial s(D6,D5);

#define WLAN_SSID       "kanna"      //mention SSID 
#define WLAN_PASS       "12345678"      //mention Password

//////////////////////////////////////////
#define FIREBASE_HOST "pollution-monitor-1e306.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"


void setup()
{
  s.begin(9600);
  Serial.begin(9600);
  while (!Serial) continue;

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
  Firebase.begin(FIREBASE_HOST);
}
 
void loop()
{
  
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
  Firebase.setInt("a",data1);
  Firebase.setInt("b",data2);
  delay(500);
}
