#include <Wire.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double Nul_compZ, Nul_compX, Nul_compY,  Nul_comp_AcX;
unsigned long timer = 0;

void rec_signal()
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  //Готовим для чтения регистры  с адреса 0x3B.
    Wire.endTransmission(false);
    // Запрос 14 регистров.
    Wire.requestFrom(MPU_addr, 14, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Tmp = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();
}

void MPU_setup()
{

    Wire.begin();
#ifdef ESP8266
    Wire.setClockStretchLimit(1000);
#endif
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);  // Производим запись в регистр энергосбережения MPU-6050
    Wire.write(0);
    Wire.endTransmission(true);
    Nul_compZ = 0;
    Nul_compX = 0;
    Nul_compY = 0;
}

void Nul_comp(float mill_sec)
{
    long ms = mill_sec;
    float i = 0;
    Nul_compZ = 0;
    Nul_compX = 0;
    Nul_compY = 0;
    timer = millis();
    unsigned long endtime = millis() + ms;
    while (endtime > timer) {
        timer = millis();
        rec_signal();
        Nul_compZ += (float)(GyZ);
        Nul_compX += (float)(GyX);
        Nul_compY += (float)(GyY);
        delay(2);
        i++;
    }
    Nul_compZ /= i;
    Nul_compX /= i;
    Nul_compY /= i;
}

