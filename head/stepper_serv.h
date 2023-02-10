#ifndef INC_STEPPER_SERV_H
#define INC_STEPPER_SERV_H
#define STEP_R 2
#define STEP_L 26
#define STP_EN_R 4
#define STP_EN_L 13
#define DIR_R 15
#define DIR_L 25
#define DIR_L_FORWARD true
#define DIR_L_BACKWARD false
#define DIR_R_FORWARD true
#define DIR_R_BACKWARD false

int32_t maxSPEED = 1000000;
int32_t minSPEED = 100000;
int32_t acceleration = 10;
int32_t accelerationL = 0;
int32_t accelerationR = 0;

volatile int32_t speed_last_L = 0;
volatile int32_t speed_last_R = 0;
volatile int32_t speed_left = 0;
volatile int32_t speed_right = 0;
volatile int32_t speed_xxx_L = 0;
volatile int32_t speed_xxx_R = 0;

bool stmot_en_lv = true;
int stop_time;

void setup_motor(){
    stmot_en_lv = true;
    pinMode(STEP_L, OUTPUT);
    pinMode(STEP_L, OUTPUT);
    pinMode(DIR_L, OUTPUT);
    pinMode(DIR_R, OUTPUT);
    pinMode(STP_EN_L, OUTPUT);
    pinMode(STP_EN_R, OUTPUT);
    digitalWrite(DIR_L, DIR_L_FORWARD);
    digitalWrite(DIR_R, DIR_R_FORWARD);
    digitalWrite(STP_EN_L, stmot_en_lv);
    digitalWrite(STP_EN_R, stmot_en_lv);
}

void off_stmot(){
    if(!stmot_en_lv){
        stmot_en_lv = true;
        digitalWrite(STP_EN_L, stmot_en_lv);
        digitalWrite(STP_EN_R, stmot_en_lv);
    }
}

void on_stmot(){
    if(stmot_en_lv){
        stmot_en_lv = false;
        digitalWrite(STP_EN_L, stmot_en_lv);
        digitalWrite(STP_EN_R, stmot_en_lv);
        delay(500);
    }
}

#endif
