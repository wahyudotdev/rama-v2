#include "main.h"
static void vBlink(void *parameters)
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    vTaskDelay(1000);
  }
}
static void vController(void *parameters)
{
  unsigned long last = 0;
  pinMode(ESP_IO, INPUT);
  Serial2.begin(115200);
  Serial.println("Ready");
  DynamicJsonDocument doc(1024);
  for (;;)
  {
    if (millis() - last > 500)
    {
      direction = 0;
    }
    if (Serial2.available() > 0)
    {
      String json = Serial2.readStringUntil('!');
      Serial2.print("r," + (String)ultrasonic1 + "," + (String)ultrasonic2 + "," + (String)ultrasonic3 + "," + (String)ultrasonic4 + "!");
      DeserializationError error = deserializeJson(doc, json);
      if (!error)
      {
        direction = doc["dir"];
        speed = (doc["speed"].as<int>() /100.00) *255;
        last = millis();
      }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

static void vMovement(void *parameters)
{
  for (;;)
  {
    // servo.write(camera);
    if (direction == 1)
    {
      Serial.println("MAJU "+(String)speed);
      base.forward(speed);
    }
    if (direction == 2)
    {
      Serial.println("KANAN "+(String)speed);
      base.rotateRight(speed);
    }
    if (direction == 3)
    {
      Serial.println("MUNDUR "+(String)speed);
      base.reverse(speed);
    }
    if (direction == 4)
    {
      Serial.println("KIRI "+(String)speed);
      base.rotateLeft(speed);
    }
    if (direction == 0)
    {
      base.brake();
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}
int getRange(byte trig, byte echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  long duration = pulseIn(echo, HIGH);
  return (duration/2) / 29.1;
}
void vUltrasonic(void *parameters)
{
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(ECHO3, INPUT);
  pinMode(ECHO4, INPUT);

  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(TRIG4, OUTPUT);
  for (;;)
  {
    ultrasonic1 = getRange(TRIG1, ECHO1);
    vTaskDelay(50);
    ultrasonic2 = getRange(TRIG2, ECHO2);
    vTaskDelay(50);
    ultrasonic3 = getRange(TRIG3, ECHO3);
    vTaskDelay(50);
    ultrasonic4 = getRange(TRIG4, ECHO4);
    vTaskDelay(50);
    // Serial.println(String(ultrasonic1)+","+(String)ultrasonic2+","+(String)ultrasonic3+","+(String)ultrasonic4);
  }
}

void EN1()
{
  m1.isrHandler();
}

void EN2()
{
  m2.isrHandler();
}

void timerIsr()
{
  m1.calculateRpm(SAMPLING_TIME);
  m2.calculateRpm(SAMPLING_TIME);
}

void setup()
{
  Serial.begin(115200);
  pinMode(ESP_IO, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(m1.en_a), EN1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(m2.en_a), EN2, FALLING);

  xTaskCreate(vBlink,
              "Blink",
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY + 1,
              &t_blink);
  xTaskCreate(vController,
              "Controller",
              configMINIMAL_STACK_SIZE + 300,
              NULL,
              tskIDLE_PRIORITY + 3,
              &t_controller);
  xTaskCreate(vMovement,
              "Movement",
              configMINIMAL_STACK_SIZE + 300,
              NULL,
              tskIDLE_PRIORITY + 2,
              &t_movement);
  xTaskCreate(vUltrasonic,
              "Ultrasonic",
              configMINIMAL_STACK_SIZE + 300,
              NULL,
              tskIDLE_PRIORITY + 2,
              &t_movement);
  vTaskStartScheduler();
}

void loop()
{
}