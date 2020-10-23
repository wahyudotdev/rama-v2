#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"

uMQTTBroker myBroker;
char ssid[] = "y";      // your network SSID (name)
char pass[] = "Kenari.123"; // your network password
void startWiFiClient()
{
  Serial.println("Connecting to "+(String)ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void startWiFiAP()
{
  WiFi.softAP(ssid, pass);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}

void setup()
{
  Serial.begin(9600);
  startWiFiClient();
  Serial.println("Starting MQTT broker");
  myBroker.init();
}

void loop()
{
  if(Serial.available()>0) myBroker.publish("data",Serial.readStringUntil('!')); 
}