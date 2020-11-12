#ifndef _ex_7_
#define _ex_7_
#include <Arduino.h>
#define DYNAMIC     1
#define STATIC      0

/*
    7 channel : AUX3, AUX2, AUX1, YAW, PITCH, ROLL, THROT
    4 channel : AUX3, YAW, PITCH, ROLL
*/
class EX7
{
private:
    byte aux1, aux2, aux3, yaw, pitch, roll, throt;
    unsigned long lastTime, now;
public:
    bool connected;
    int getAux1();
    int getAux2();
    int getAux3();
    int getYaw();
    int getPitch();
    int getRoll();
    int getThrot();
    int y();
    int x();
    int rotate();
    int speed();
    int cameraDegree();
    EX7(byte yaw, byte pitch, byte roll, byte throt);
    EX7(byte aux3, byte aux2, byte aux1, byte yaw, byte pitch, byte roll, byte throt);
};

#endif