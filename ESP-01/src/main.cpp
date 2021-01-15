#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "uMQTTBroker.h"
#include "subscribe.h"
#define LED 2
uMQTTBroker myBroker;
Ticker tick;
char ssid[] = "Telkom IoT"; // your network SSID (name)
char pass[] = "0987654321"; // your network password
char apssid[] = "RAMA";

void startWiFiAP()
{
  WiFi.disconnect();
  WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  WiFi.hostname("rama");
  WiFi.softAP(apssid, pass);
  Serial.println("Soft AP Started");
}
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
    if (millis() > 10000)
    {
      startWiFiAP();
      break;
    }
  }
  digitalWrite(LED, LOW);
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void ICACHE_RAM_ATTR gas()
{
  digitalWrite(LED, !digitalRead(LED));
}
void setup()
{
  int wait_time_ms = 1;
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  tick.attach_ms(wait_time_ms, gas);
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
  if (Serial.available() > 0)
    myBroker.publish("encoder", Serial.readStringUntil('!'));
}