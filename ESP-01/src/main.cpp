/*
RX      3v3
IO0     RST
IO2     EN
GND     TX

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include "subscribe.h"
#include <PubSubClient.h>
#define LED         2
#define MQTT_BROKER "192.168.0.50"
#define MQTT_PORT   1883
const char id[5]=          "rama";
// Apabila konek ke hotspot maka status false, jika AP aktif maka true
bool isSoftAp;
MyBroker myBroker;
WiFiClient espClient;
PubSubClient client(espClient);
char ssid[] = "Telkom IoT";    // your network SSID (name)
char pass[] = "0987654321"; // your network password
char apssid[] = "RAMA";
char *topic;
void callback(char *topic, byte *payload, unsigned int length)
{
    char buff[length];
    for (unsigned int i = 0; i < length; i++)
    {
        buff[i] = (char)payload[i];
    }
    Serial.print(buff);
    Serial.write('!');
}

void startWiFiAP()
{
    WiFi.disconnect();
    WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
    WiFi.hostname("rama");
    WiFi.softAP(apssid, pass);
    // Serial.println("Soft AP Started");
    // Serial.println("Starting MQTT broker");
    myBroker.init();
}

void startWiFiClient()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    // Serial.println("Connecting to " + (String)ssid);
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        digitalWrite(LED, !digitalRead(LED));
    }
    // WiFi.config(IPAddress(192,168,254,101), IPAddress(192,168,254,254), IPAddress(255,255,255,0));
    if (isSoftAp == false)
    {
        client.setServer(MQTT_BROKER, MQTT_PORT);
        client.setCallback(callback);
        client.connect("rama_bot");
        client.subscribe("rama/controller");
    }
    // Serial.println("IP address: " + WiFi.localIP().toString());
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    startWiFiClient();
    digitalWrite(LED, LOW);
}

unsigned long last;
void loop()
{
    if(millis()-last > 1000){
        client.publish("rama/ip",WiFi.localIP().toString().c_str());
        last = millis();
    }
    if (WiFi.status() != WL_CONNECTED)
    {
        startWiFiClient();
    }
    if (client.state() != MQTT_CONNECTED)
    {
        client.connect("rama_bot");
        client.subscribe("rama/controller");
    }
    if (Serial.available() > 0)
    {
        if (isSoftAp)
        {
            myBroker.publish("rama/sensor", Serial.readStringUntil('!'));
        }
        else
        {
            client.publish("rama/sensor", Serial.readStringUntil('!').c_str());
        }
    }
    if (isSoftAp == false)
        client.loop();
}