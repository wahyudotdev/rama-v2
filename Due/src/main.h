#include <Arduino.h>

/*
    Untuk Due menggunakan DueTimer, untuk mega menggunakan
    TimerOne
*/
#if (SAM3XA_SERIES) || (SAM3N_SERIES) || (SAM3S_SERIES)
#include <DueTimer.h>
#else
#include <TimerOne.h>
#endif

#include <Motor.h>
#include <Kinematic.h>
#include <EX7.h>

#define SAMPLING_TIME   100

#define EN1_A   2
#define EN1_B   4
#define M1_A    8
#define M1_B    7
#define M1_PWM  6

#define EN2_A   3
#define EN2_B   5
#define M2_A    11
#define M2_B    10
#define M2_PWM  9


// pin remot gan
#define AUX3    40
#define AUX2    42
#define AUX1    44
#define YAW     46
#define PITCH   48
#define ROLL    50
#define THROT   52

/* Inisialisasi library
 */
Motor m1(M1_A, M1_B, M1_PWM, EN1_A, EN1_B);
Motor m2(M2_A, M2_B, M2_PWM, EN2_A, EN2_B);
EX7 ex7(AUX3, AUX2, AUX1, YAW, PITCH, ROLL, THROT);
Kinematic base(m1, m2);

// inisialisasi fungsi
void EN1(void); void EN2(void); void timerIsr(void);