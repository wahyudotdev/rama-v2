#ifndef _kinematic_h
#define _kinematic_h
#include <Arduino.h>
#include <Motor.h>

#define BASIC

/**
    #define BASIC   => kinematic 2 roda 
    #define OMNI    => kinematic 3 roda omni
    #define MECANUM => kinematic 4 roda mecanum
*/
class Kinematic
{
private:
    Motor *m1, *m2, *m3, *m4;

public:
#if defined(BASIC)
    Kinematic(Motor &m1, Motor &m2);
    void forward(int speed);
    void reverse(int speed);
    void rotateRight(int speed);
    void rotateLeft(int speed);
    void brake();
#elif defined(OMNI)
    Kinematic(Motor &m1, Motor &m2, Motor &m3);
    void forward(int speed);
    void reverse(int speed);
    void shiftRight(int speed);
    void shiftLeft(int speed);
    void rotateRight(int speed);
    void rotateLeft(int speed);
#elif defined(MECANUM)
    Kinematic(Motor &m1, Motor &m2, Motor &m3, Motor &m4);
    void forward(int speed);
    void reverse(int speed);
    void shiftRight(int speed);
    void shiftLeft(int speed);
    void rotateRight(int speed);
    void rotateLeft(int speed);
#endif
};

#endif