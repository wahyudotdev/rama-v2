#include "Kinematic.h"

#if defined(BASIC)
Kinematic::Kinematic(Motor &m1, Motor &m2)
{
    this->m1 = &m1;
    this->m2 = &m2;
}
void Kinematic::forward(int speed)
{
    m1->speed(speed);
    m2->speed(speed);
}

void Kinematic::reverse(int speed)
{
    m1->speed(-speed);
    m2->speed(-speed);
}

void Kinematic::rotateLeft(int speed)
{
    m1->speed(-speed);
    m2->speed(speed);
}

void Kinematic::rotateRight(int speed)
{
    m1->speed(speed);
    m2->speed(-speed);
}

void Kinematic::brake(){
    m1->brake();
    m2->brake();
}
#elif defined(OMNI)
Kinematic::Kinematic(Motor &m1, Motor &m2, Motor &m3)
{
    this->m1 = &m1;
    this->m2 = &m2;
    this->m3 = &m3;
}
void Kinematic::forward(int speed)
{
    Serial.println("Maju OMNI");
}
#elif defined(MECANUM)
Kinematic::Kinematic(Motor &m1, Motor &m2, Motor &m3, Motor &m4)
{
    this->m1 = &m1;
    this->m2 = &m2;
    this->m3 = &m3;
    this->m4 = &m4;
}
void Kinematic::forward(int speed)
{
    m1->speed(speed);
    m2->speed(-speed);
    m3->speed(speed);
    m4->speed(-speed);
}
void Kinematic::reverse(int speed)
{
    m1->speed(-speed);
    m2->speed(speed);
    m3->speed(-speed);
    m4->speed(speed);
}
void Kinematic::shiftRight(int speed)
{
    m1->speed(speed);
    m2->speed(speed);
    m3->speed(-speed);
    m4->speed(-speed);
}
void Kinematic::shiftLeft(int speed)
{
    m1->speed(-speed);
    m2->speed(-speed);
    m3->speed(speed);
    m4->speed(speed);
}
#else
#error "Setting dulu kinematik di Kinematic.h"
#endif