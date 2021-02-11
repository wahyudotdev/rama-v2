#include <Arduino.h>
// #include <Pwm.h>
#define RAMAV2
/*
    Untuk Due menggunakan DueTimer, untuk mega menggunakan
    TimerOne
*/
#if (SAM3XA_SERIES) || (SAM3N_SERIES) || (SAM3S_SERIES)
#include <FreeRTOS_ARM.h>
#include <ArduinoJson.h>
#define SYSRESETREQ    (1<<2)
#define VECTKEY        (0x05fa0000UL)
#define VECTKEY_MASK   (0x0000ffffUL)
#define AIRCR          (*(uint32_t*)0xe000ed0cUL) // fixed arch-defined address
#define REQUEST_EXTERNAL_RESET (AIRCR=(AIRCR&VECTKEY_MASK)|VECTKEY|SYSRESETREQ)
#else
// #include <TimerOne.h>
#endif

#include <Motor.h>
#include <Kinematic.h>
#include <EX7.h>
#include <Servo.h>
#define SAMPLING_TIME   100

#if defined(RAMAV1)

#define M1_A    22
#define M1_B    23
#define M1_PWM  9
#define EN1_A   3
#define EN1_B   11

#define M2_A    24
#define M2_B    25
#define M2_PWM  8
#define EN2_A   2
#define EN2_B   10

#define M3_A    26
#define M3_B    27
#define M3_PWM  7
#define EN3_A   18
#define EN3_B   14

#define M4_A    29
#define M4_B    28
#define M4_PWM  6
#define EN4_A   19
#define EN4_B   15


// Rama V1
#define AUX3    33
#define AUX2    40
#define AUX1    41
#define YAW     42
#define PITCH   46
#define ROLL    48
#define THROT   52

#elif defined(RAMAV2)
#define EN1_A   2
#define EN1_B   4
#define M1_A    8
#define M1_B    7
#define M1_PWM  6

#define EN2_A   3
#define EN2_B   5
#define M2_A    10
#define M2_B    11
#define M2_PWM  9
// pin remot gan
#define AUX3    52
#define AUX2    50
#define AUX1    48
#define YAW     46
#define PITCH   44
#define ROLL    42
#define THROT   40

#define ESP_IO  18

#define TRIG1   23
#define TRIG2   31
#define TRIG3   27
#define TRIG4   35

#define ECHO1   25
#define ECHO2   33
#define ECHO3   29
#define ECHO4   37

#define srvPin  38
#endif
/* Inisialisasi library
 */

#if defined(RAMAV1)
Motor m1(M1_A, M1_B, M1_PWM, EN1_A, EN1_B);
Motor m2(M2_A, M2_B, M2_PWM, EN2_A, EN2_B);
Motor m3(M3_A, M3_B, M3_PWM, EN3_A, EN3_B);
Motor m4(M4_A, M4_B, M4_PWM, EN4_A, EN4_B);
Kinematic base(m1, m2, m3, m4);

#elif defined(RAMAV2)
Motor m1(M1_A, M1_B, M1_PWM, EN1_A, EN1_B);
Motor m2(M2_A, M2_B, M2_PWM, EN2_A, EN2_B);
Kinematic base(m1, m2);
#endif
// EX7 ex7(AUX3, AUX2, AUX1, YAW, PITCH, ROLL, THROT);

Servo servo;
// inisialisasi fungsi
void EN1(void); void EN2(void); void timerIsr(void);

volatile int x,y,rotate;
uint32_t last=0, now;
volatile bool isConnected;

TaskHandle_t t_blink;
TaskHandle_t t_controller;
TaskHandle_t t_movement;
TaskHandle_t t_ultrasonic;

static void vBlink(void *parameters);
static void vController(void *parameters);
static void vUltrasonic(void *parameters);
static int getRange(byte trig, byte echo);
volatile int direction;
volatile int camera;
volatile int ultrasonic1, ultrasonic2, ultrasonic3, ultrasonic4;
volatile int speed;