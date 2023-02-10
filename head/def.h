loat alfa = 0.001;

int32_t dt;
int32_t t0;
int32_t t2;

double  GyXsum0;
double r = 0.03;

int32_t t_period;
double CommandSpeed = 0;
double OldCommandSpeed = 0;
double Turn = 0;

volatile int32_t counter_stepL;
volatile int32_t counter_stepR;
bool flag_crash = true;
double XSpeed = 0;
double  OldXSpeed = 0;

int32_t XL, XR;
int32_t OldCommandSpeed_dMove = 0;
uint32_t time_stop_move=0;

double  Kfi = 0.0158;
double  Kdfi = 0.0209;
double  Ka = 2.0274;
double  Kda = 0.3133;

double Speed = 0;
double OldSpeed = 0;
double OldGyro = 0;

double Acsel = 0;
double Gyro = 0;
double AcYsum = 0;
double _1_d_131 = 1.0/131.0;

double Move = 0; //Пройденный путь.
double dMove = 0;
double dMoveOld = 0;
double dGyro = 0;
double GyroOld = 0;

