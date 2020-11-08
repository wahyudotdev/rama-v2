#include "main.h"

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
  Serial.begin(9600);
  // servo.attach()
  // pinMode(10, INPUT);
  // m1.pid(5, 0.1, 0.4, 2000);
  // m2.pid(5, 0.1, 0.4, 2000);
  // pinMode(M1_A, OUTPUT);
  // pinMode(M1_B, OUTPUT);
  // pinMode(M1_PWM, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(m1.en_a), EN1, FALLING);
  attachInterrupt(digitalPinToInterrupt(m2.en_a), EN2, FALLING);

#if defined(RAMAV1)
  attachInterrupt(digitalPinToInterrupt(m3.en_a), EN3, FALLING);
  attachInterrupt(digitalPinToInterrupt(m4.en_a), EN4, FALLING);
#endif
#if (SAM3XA_SERIES) || (SAM3N_SERIES) || (SAM3S_SERIES)
  // Timer1.attachInterrupt(timerIsr).start(SAMPLING_TIME * 1000);
#else
  Timer1.initialize(100000);
  Timer1.attachInterrupt(timerIsr);
#endif
}

void loop()
{
  /*
    Remot terputus maka nilai Aux3 akan maksimum, Aux3 = cameraDegree
  */
 Serial.println(pulseInLong(YAW, HIGH));
  //  digitalWrite()
  // m1.speed(15);
  // Serial.println("X : " + (String)ex7.x() + " Y : " + (String)ex7.y() + " Rotate : " + (String)ex7.rotate());
  // int x = ex7.x();
  // int y = ex7.y();
  // int rotate = ex7.rotate();
  // if (abs(y) > 100 && abs(rotate < 100))
  // {
  //   y > 0 ? base.forward(y) : base.reverse(y * -1);
  // }
  // else if (abs(rotate) > 100)
  // {
  //   rotate > 0 ? base.rotateRight(rotate) : base.rotateLeft(rotate * -1);
  // }
  // else
  //   base.brake();
  // m1.speed(255);
  // m2.speed(255);
  // digitalWrite(M1_A ,HIGH);
  // digitalWrite(M2_A, HIGH);
  // digitalWrite(M1_PWM, HIGH);
  // digitalWrite(M2_PWM, HIGH);
  // digitalWrite(M1_B, HIGH);
  // digitalWrite(M2_B, HIGH);
  // digitalWrite(M1_A, LOW);
  // digitalWrite(M2_A, LOW);
  // digitalWrite(M1_PWM, LOW);
  // digitalWrite(M2_PWM, LOW);
  // digitalWrite(M1_B, LOW);
  // digitalWrite(M2_B, LOW);
}