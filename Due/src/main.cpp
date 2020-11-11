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

int count;
void loop()
{
  Serial2.print("Hallo dari Due : "+(String)count);
  Serial2.write('!');
  count++;
  delay(1000);
  // servo.write(180);
  // delay(2000);
  // servo.write(0);
  // delay(2000);
  // for(int i = 0 ; i < 180 ; i++){
  //   servo.write(i);
  //   delay(20);
  // }
  // for(int i = 180; i > 0 ; i--){
  //   servo.write(i);
  //   delay(20);
  // }
  /*
    Remot terputus maka nilai Aux3 akan maksimum, Aux3 = cameraDegree
  */
  // Serial.println("X : " + (String)ex7.x() + " Y : " + (String)ex7.y() + " Rotate : " + (String)ex7.rotate());
  // int x = ex7.x();
  // int y = ex7.y();
  // int rotate = ex7.rotate();
  // if (abs(y) > 50 && abs(rotate < 50))
  // {
  //   y > 0 ? base.forward(y) : base.reverse(y * -1);
  // }
  // else if (abs(rotate) > 50)
  // {
  //   rotate > 0 ? base.rotateRight(rotate) : base.rotateLeft(rotate * -1);
  // }
  // else
  //   base.brake();
}