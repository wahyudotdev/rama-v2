#include "EX7.h"

/*
    Setting mode 4 channel
    Aux3    -> kontrol servo
    Yaw     -> kontrol posisi X
    Pitch   -> kontrol posisi Y
    Roll    -> rotate robot
*/
EX7::EX7(byte aux3, byte yaw, byte pitch, byte roll)
{
    this->aux3 = aux3;
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
}

/*
    Setting mode 7 channel
    Aux3    -> kontrol servo
    Aux2    -> switch
    Aux1    -> switch
    Yaw     -> kontrol posisi X
    Pitch   -> kontrol posisi Y
    Roll    -> rotate robot
    Throttle-> atur kecepatan
*/
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


/*
    range nilai antara 990 - 1970
*/
int EX7::getAux3(){
    Serial.flush();
    return pulseInLong(aux3, HIGH);
}


/*
    range nilai antara 980 - 1900
*/
int EX7::getYaw(){
    Serial.flush();
    return pulseInLong(yaw, HIGH);
}


/*
    range nilai antara 990 - 1850
*/
int EX7::getPitch(){
    Serial.flush();
    return pulseInLong(pitch, HIGH);
}

/*
    range nilai antara 990 - 1900
*/
int EX7::getRoll(){
    Serial.flush();
    return pulseInLong(roll, HIGH);
}
int EX7::getThrot(){
    Serial.flush();
    return pulseInLong(throt, HIGH);
}

/*
    Didapat dari nilai tombol pitch kontroller, positif
    jika ke atas dan negatif jika kebawah. Gunakan untuk maju
    dan mundur robot
*/
int EX7::y()
{
    return map(getPitch(), 980, 1850, -255, 255);
}

/*
    Didapat dari nilai tombol Roll kontroller, nilai akan
    positif jika roll kekanan, negatif jika kekiri. Gunakan
    nilai ini untuk sliding posisi robot (hanya base X, Y, dan plus)
*/
int EX7::x()
{
    return map(getRoll(), 1900, 1000, -255 , 255);
}

/*
    Nilai didapat dari tombol Yaw pada kontroller.
    Apabila Yaw ke kanan maka nilai akan positif,
    jika Yaw ke kiri akan negatif. Gunakan nilai ini
    untuk memutar posisi robot
*/
int EX7::rotate()
{
    return map(getYaw() , 1850, 980, -255, 255);
}
/*
    Nilai didapat dari Aux3 controller,
    digunakan untuk mengontrol servo. Nilai akan max
    saat kontroller terputus
*/
int EX7::cameraDegree(){
    int deg = abs(map(getAux3(),980, 1970,0,360));
    deg > 350? connected = false : connected = true;
    return deg/2;
}
