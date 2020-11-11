#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "uMQTTBroker.h"
#define LED 2
uMQTTBroker myBroker;
Ticker tick;
char ssid[] = "bolt";          // your network SSID (name)
char pass[] = "11111111"; // your network password
void startWiFiClient()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.println("Connecting to " + (String)ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED, !digitalRead(LED));
    delay(300);
    Serial.print(".");
  }
  digitalWrite(LED, LOW);
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void startWiFiAP()
{
  WiFi.softAP(ssid, pass);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}


void ICACHE_RAM_ATTR gas(){
  digitalWrite(LED, !digitalRead(LED));
}
void setup()
{
  int wait_time_ms = 1;
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  tick.attach_ms(wait_time_ms,gas);
  Serial.println("Ready : ");
  
  // while (true)
  // {
  //   if (Serial.available() > 0)
  //   {
  //     String data = Serial.readString();
  //     wait_time_ms = data.toInt();
  //     tick.detach();
  //     tick.attach_ms(wait_time_ms, gas);
  //     Serial.println("Generate pulse every : "+(String)wait_time_ms+" ms");
  //   }
  // }

  startWiFiClient();
  Serial.println("Starting MQTT broker");
  myBroker.init();
}

void loop()
{
  if(Serial.available()>0) myBroker.publish("data",Serial.readStringUntil('!'));
}