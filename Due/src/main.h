#include <Arduino.h>
#include <DueTimer.h>
#include <Motor.h>
#include <Kinematic.h>

#define EN1_A   2
#define EN1_B   3
#define M1_A    4
#define M1_B    5
#define M2_A    7
#define M2_B    8
#define M2_PWM  9
#define M1_PWM  6

Motor m1(M1_A, M1_B, M1_PWM, EN1_A, EN1_B, 40);
Motor m2(M2_A, M2_B, M2_PWM);
Motor m3(M2_A, M2_B, M2_PWM);
Motor m4(M2_A, M2_B, M2_PWM);
// Kinematic base(m1, m2, m3, m4);
volatile byte timer_tick = 1;