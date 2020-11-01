#include <Arduino.h>
#include "Motor.h"

Motor::Motor(byte a_pin, byte b_pin, byte pwm_pin)
{
    this->a_pin = a_pin;
    this->b_pin = b_pin;
    this->pwm_pin = pwm_pin;

    pinMode(this->a_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
    pinMode(this->pwm_pin, OUTPUT);
    // setPwmFrequency();
}
Motor::Motor(byte a_pin, byte b_pin, byte pwm_pin, byte en_a, byte en_b)
{
    this->a_pin = a_pin;
    this->b_pin = b_pin;
    this->pwm_pin = pwm_pin;
    this->en_a = en_a;
    this->en_b = en_b;
    pinMode(this->a_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
    pinMode(this->pwm_pin, OUTPUT);
    pinMode(this->en_a, INPUT_PULLUP);
    pinMode(this->en_b, INPUT_PULLUP);
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, LOW);
    digitalWrite(this->pwm_pin, LOW);
    // setPwmFrequency();
}
Motor::Motor(byte a_pin, byte b_pin, byte pwm_pin, byte en_a, byte en_b, int ppr)
{
    this->a_pin = a_pin;
    this->b_pin = b_pin;
    this->pwm_pin = pwm_pin;
    this->en_a = en_a;
    this->en_b = en_b;
    this->ppr = ppr;
    pinMode(this->a_pin, OUTPUT);
    pinMode(this->b_pin, OUTPUT);
    pinMode(this->pwm_pin, OUTPUT);
    pinMode(this->en_a, INPUT_PULLUP);
    pinMode(this->en_b, INPUT_PULLUP);
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, LOW);
    digitalWrite(this->pwm_pin, LOW);
    // setPwmFrequency();
}
/*
    Kp, Ki, Kd, Windup
*/
void Motor::pid(float kp, float ki, float kd, float windup)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->windup = windup;
    this->pidEnable = true;
}
void Motor::setPidThreshold(int min_pwm, int max_pwm)
{
    this->min_pwm = min_pwm;
    this->max_pwm = max_pwm;
}
void Motor::speed(int target)
{
    if (pidEnable == true)
    {
        err = abs(target) - rpm;
        abs(mIntegral < windup) ? mIntegral += err : mIntegral = 0;
        pwmPid = (kp * err * 0.1) + (ki * mIntegral * 0.01) + (kd * (err - lastErr) * 0.1);
        lastErr = err;
        pwmPid = abs(target) + pwmPid;
        if (pwmPid < min_pwm)
        {
            pwmPid = min_pwm;
        }
        else if (pwmPid > max_pwm)
        {
            pwmPid = max_pwm;
        }
        Serial.println("kp : " + (String)kp + " ki : " + (String)ki + " kd : " + (String)kd + " pwm :" + (String)pwmPid);
        target > 0 ? forward(pwmPid) : reverse(pwmPid);
    }
    else
    {
        if(target > 255) target = 255;
        else if (target < -255) target = -255;
        target > 0 ? forward(target) : reverse(target);
    }
}

void Motor::forward(int pwm)
{
    if(abs(pwm) < threshold) pwm = 0;
    digitalWrite(this->a_pin, HIGH);
    digitalWrite(this->b_pin, LOW);
    analogWrite(this->pwm_pin, pwm);
}

void Motor::reverse(int pwm)
{
    if(abs(pwm) < threshold) pwm = 0;
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, HIGH);
    analogWrite(this->pwm_pin, abs(pwm));
}

#if defined(EMS)
void Motor::brake()
{
    digitalWrite(this->a_pin, HIGH);
    digitalWrite(this->b_pin, HIGH);
}
#else
void Motor::brake()
{
    digitalWrite(this->a_pin, LOW);
    digitalWrite(this->b_pin, LOW);
}
#endif

void Motor::isrHandler()
{
    digitalRead(b_pin) == HIGH ? encoder_tick++ : encoder_tick--;
}

void Motor::calculateRpm(int sampling_time_ms)
{
#if (SAM3XA_SERIES) || (SAM3N_SERIES) || (SAM3S_SERIES)
    sampling_time_ms = sampling_time_ms / 2;
#endif
    rpm = abs((encoder_tick / ppr) * (60000 / sampling_time_ms));
    encoder_tick = 0;
}

void Motor::setPwmThreshold(int threshold){
    this->threshold = threshold;
}
