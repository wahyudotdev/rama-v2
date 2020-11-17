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
  Serial2.begin(115200);
  Serial2.print("bolt");
  Serial2.write(13);
  Serial2.print("11111111");
  Serial2.write(13);
  servo.attach(srvPin);
  // pinMode(10, INPUT);
  // m1.pid(5, 0.1, 0.4, 2000);
  // m2.pid(5, 0.1, 0.4, 2000);
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
  int y = ex7.y();
  int rotate = ex7.rotate();
  int cameraDeg = ex7.cameraDegree();
  // base.rotateLeft(255);
  // m1.speed(255);
  // m2.speed(255);
  // Serial.println("Aux 3 : "+(String)ex7.getAux3()+"  camera : "+(String)ex7.cameraDegree()+" connected : "+(String)ex7.connected);
  servo.write(cameraDeg);
  if (ex7.connected && (abs(y)> 50 || abs(rotate)> 50))
  {
    if (abs(rotate) < 50)
    {
      Serial.println("Maju mundur");
      y > 0 ? base.forward(y) : base.reverse(y);
    }
    else
    {
      Serial.println("muter");
      rotate > 0 ? base.rotateRight(rotate) : base.rotateLeft(rotate);
    }
  }
  else
  {
    Serial.println("Mandek");
    base.brake();
  }
}