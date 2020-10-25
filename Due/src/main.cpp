#include "main.h"

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
  m1.calculateRpm(100);
  m2.calculateRpm(100);
  m3.calculateRpm(100);
  m4.calculateRpm(100);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Hallo");
  // m1.pid(1, 0.1, 0.4, 2000);
  attachInterrupt(digitalPinToInterrupt(m1.en_a), EN1, FALLING);
  attachInterrupt(digitalPinToInterrupt(m2.en_a), EN2, FALLING);
  Timer.attachInterrupt(timerIsr).start(100000);
}

void loop()
{
  // delay(1000);
  Serial.println("RPM "+(String)m1.rpm);
  delay(1000);
  // m1.speed(-10);
  // base.reverse(50);
  // m1.speed(100);
  // delay(1000);
}