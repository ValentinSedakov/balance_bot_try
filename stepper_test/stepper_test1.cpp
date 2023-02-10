#include <Arduino.h>

#define EN 4
#define STEP 2
#define DIR 15

int cu_num_stps = 0;      // текущий номер шага
int max_num_st = 600;     // максимальное число шагов 
int microsec_to_one_step = 3000; //мкс.
unsigned long timer; // так как micros() - число микросекунд от начала работы программы ulong

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(EN, 1); // до завершения предварительной настройки двигатель отключен
  digitalWrite(STEP, 0);
  digitalWrite(DIR,1);
  timer = micros() + microsec_to_one_step; // приводим к единицам мкс
  digitalWrite(EN, 0); // включаем двигатель
  Serial.println("test 1 begins");

}

void loop() {
  unsigned long ctrl_st_drtn;     //control step duration
  ctrl_st_drtn = micros();

  if(ctrl_st_drtn >= timer) {

    if (cu_num_stps < max_num_st){
        timer += microsec_to_one_step;
        digitalWrite(STEP, 1);
        delayMicroseconds(10);
        digitalWrite(STEP, 0);
        cu_num_stps++;
    }
    else if(cu_num_stps == max_num_st)  {
        Serial.println("motor is stopping");
        delay(500);                   // гашение инерции мотора, ждем в мс
        digitalWrite(EN, 1);          // отключаем движок
        Serial.println("motor has stopped");
        cu_num_stps++;
    }
  }
}