#include <Arduino.h>
#include <FreeRTOS_ARM.h>
#include <ArduinoJson.h>
#include <Motor.h>
#include <Kinematic.h>
#include <EX7.h>
#include <Servo.h>

#define SAMPLING_TIME   100

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

/* Inisialisasi motor dan kinematik
 */

Motor m1(M1_A, M1_B, M1_PWM, EN1_A, EN1_B);
Motor m2(M2_A, M2_B, M2_PWM, EN2_A, EN2_B);
Kinematic base(m1, m2);

Servo servo;

// inisialisasi fungsi
void EN1(void); void EN2(void); void timerIsr(void);

// Inisialisasi variabel global
volatile int x,y,rotate;
uint32_t last=0, now;
volatile bool isConnected;
volatile int direction;
volatile int camera;
volatile int ultrasonic1, ultrasonic2, ultrasonic3, ultrasonic4;
volatile int speed;

// Inisialisasi Task Handler untuk FreeRTOS
TaskHandle_t t_blink;
TaskHandle_t t_controller;
TaskHandle_t t_movement;
TaskHandle_t t_ultrasonic;


// Inisialisasi pointer fungsi RTOS
static void vBlink(void *parameters);
static void vController(void *parameters);
static void vUltrasonic(void *parameters);
static int getRange(byte trig, byte echo);