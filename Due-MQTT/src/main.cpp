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
  unsigned long last;
  pinMode(ESP_IO, INPUT);
  Serial2.begin(115200);
  Serial.println("Ready");
  DynamicJsonDocument doc(1024);
  unsigned long l;
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
        camera = doc["cam"];
        // speed = doc["speed"]>0?doc["speed"]:speed=150;
        if (doc["speed"] > 0)
        {
          speed = doc["speed"];
        }
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
      Serial.println("MAJU");
      base.forward(255);
    }
    if (direction == 2)
    {
      Serial.println("KANAN");
      base.rotateRight(255);
    }
    if (direction == 3)
    {
      Serial.println("MUNDUR");
      base.reverse(255);
    }
    if (direction == 4)
    {
      Serial.println("KIRI");
      base.rotateLeft(255);
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
    Serial.println(String(ultrasonic1)+","+(String)ultrasonic2+","+(String)ultrasonic3+","+(String)ultrasonic4);
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
#if defined(RAMAV1)
void EN3()
{
  m3.isrHandler();
}
void EN4()
{
  m4.isrHandler();
}
#endif

void timerIsr()
{
  m1.calculateRpm(SAMPLING_TIME);
  m2.calculateRpm(SAMPLING_TIME);
#if defined(RAMAV1)
  m3.calculateRpm(SAMPLING_TIME);
  m4.calculateRpm(SAMPLING_TIME);
#endif
}

void setup()
{
  Serial.begin(115200);
  pinMode(ESP_IO, INPUT_PULLUP);
  // pinMode(10, INPUT);
  // m1.pid(5, 0.1, 0.4, 2000);
  // m2.pid(5, 0.1, 0.4, 2000);
  // pinMode(TRIG3, OUTPUT);
  // pinMode(ECHO3, INPUT);
  // while (true)
  // {
  //   Serial.println(getRange(TRIG3, ECHO3));
  //   delay(100);
  // }

  attachInterrupt(digitalPinToInterrupt(m1.en_a), EN1, FALLING);
  attachInterrupt(digitalPinToInterrupt(m2.en_a), EN2, FALLING);

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