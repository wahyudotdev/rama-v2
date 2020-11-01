#include "EX7.h"

/*
    Tes tes
**/
EX7::EX7(byte yaw, byte pitch, byte roll, byte throt)
{
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
    this->throt = throt;
}

/*
    Tes tes
**/
EX7::EX7(byte aux3, byte aux2, byte aux1, byte yaw, byte pitch, byte roll, byte throt)
{
    this->aux3 = aux3;
    this->aux2 = aux2;
    this->aux1 = aux1;
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
    this->throt = throt;
}

int EX7::getAux1(){
    Serial.flush();
    return pulseInLong(aux1, HIGH);
}
int EX7::getAux2(){
    Serial.flush();
    return pulseInLong(aux2, HIGH);
}

// 980 - 1970
int EX7::getAux3(){
    Serial.flush();
    return pulseInLong(aux3, HIGH);
}

// 980 - 1900
int EX7::getYaw(){
    Serial.flush();
    return pulseInLong(yaw, HIGH);
}

// 980 - 1850
int EX7::getPitch(){
    Serial.flush();
    return pulseInLong(pitch, HIGH);
}

// 990 - 1900
int EX7::getRoll(){
    Serial.flush();
    return pulseInLong(roll, HIGH);
}
int EX7::getThrot(){
    Serial.flush();
    return pulseInLong(throt, HIGH);
}

int EX7::y()
{
    return map(getPitch(), 980, 1850, -255, 255);
}
int EX7::rotate()
{
    return map(getYaw() , 980, 1850, -255, 255);
}
int EX7::cameraDegree(){
    return abs(map(getAux3(), 980, 1970, 0, 360));
}
