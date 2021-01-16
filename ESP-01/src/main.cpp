#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include "subscribe.h"
#include <PubSubClient.h>
#define LED 2
#define MQTT_BROKER "192.168.43.44"
#define MQTT_PORT 1883
// Apabila konek ke hotspot maka status false, jika AP aktif maka true
bool isSoftAp;
MyBroker myBroker;
WiFiClient espClient;
PubSubClient client(espClient);
char ssid[] = "bolt";     // your network SSID (name)
char pass[] = "11111111"; // your network password
char apssid[] = "RAMA";
char *topic="rama";

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
    if (isSoftAp == false)
    {
        client.setServer(MQTT_BROKER, MQTT_PORT);
        client.setCallback(callback);
        client.connect("rama_bot");
        client.subscribe("controller");
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

void loop()
{
    if(WiFi.status() != WL_CONNECTED){
        startWiFiClient();
    }
    if (Serial.available() > 0)
    {
        if (isSoftAp)
        {
            myBroker.publish(topic, Serial.readStringUntil('!'));
        }
        else
        {
            client.publish(topic, Serial.readStringUntil('!').c_str());
        }
    }
    if (isSoftAp == false)
        client.loop();
}