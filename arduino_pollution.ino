#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);

 
void setup() {
  s.begin(9600);
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop()
{
 
 
  root["p1"]= analogRead(A0);
  Serial.print("pollution level 1  ");
  Serial.println(analogRead(A0));
  root["p2"]= analogRead(A1);
  Serial.print("pollution level 2  ");
  Serial.println(analogRead(A1));
  delay(500);
 
if(s.available()>0)
{
 root.printTo(s);
}
}
