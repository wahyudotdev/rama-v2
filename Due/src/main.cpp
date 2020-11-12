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
  m1.pid(5, 0.1, 0.4, 2000);
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
  servo.write(ex7.cameraDegree());
  if(ex7.connected){
    if(abs(ex7.rotate())> 0){
      ex7.y() > 0 ? base.forward(ex7.y()): base.reverse(ex7.y());
    }
    else{
      ex7.rotate() > 0 ? base.rotateRight(ex7.rotate()) : base.rotateLeft(ex7.rotate());
    }
  }
}