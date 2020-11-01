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
  m1.calculateRpm(SAMPLING_TIME);
  m2.calculateRpm(SAMPLING_TIME);
}

void setup()
{
  Serial.begin(9600);
  // pinMode(10, INPUT);
  m1.pid(5, 0.1, 0.4, 2000);
  m2.pid(5, 0.1, 0.4, 2000);
  attachInterrupt(digitalPinToInterrupt(m1.en_a), EN1, FALLING);
  attachInterrupt(digitalPinToInterrupt(m2.en_a), EN2, FALLING);
#if (SAM3XA_SERIES) || (SAM3N_SERIES) || (SAM3S_SERIES)
  Timer1.attachInterrupt(timerIsr).start(SAMPLING_TIME * 1000);
#else
  Timer1.initialize(SAMPLING_TIME * 1000);
  Timer1.attachInterrupt(timerIsr);
#endif
}

void loop()
{
  /*
    Remot terputus maka nilai Aux3 akan maksimum, Aux3 = cameraDegree
  */
  delay(1);
  // Serial.println("camera degree : " + (String)ex7.cameraDegree());
  if (ex7.cameraDegree() < 350)
  {
    if (abs(ex7.rotate()) < 50)
      ex7.y() > 0 ? base.forward(ex7.y()) : base.reverse(abs(ex7.y()));
    else
      ex7.rotate() > 0 ? base.rotateRight(ex7.rotate()) : base.rotateLeft(abs(ex7.rotate()));
  }
  else base.brake();
}