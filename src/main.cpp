#include <Arduino.h>
#include <stdint.h>
#include <BluetoothSerial.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

#include "def.h"
#include "MPU6050.h"
#include "StepperServ.h"  //Описание моторов
#include "interr_ion.h"  //Работа с прерываниями
#include "Bt_move.h"  //Реагирование на команды
#define one_KF 0.01
#define KF 0.99

void setup() {

  setup_motor();
  off_stmot();
  timer_setup();

  Serial.begin(115200);
  Serial.println();

  SerialBT.begin("Balans_bt");
  MPU_setup();
  delay(100);
  Nul_comp(4000);
  t0 = micros() - 5000;
  t2 = micros();
  Speed = 0;
  flag_crash = true;
  time_start_move = millis();
  time_stop_move = millis();
}

uint32_t micros_;
void loop()
{
  int32_t speed_L ;
  int32_t speed_R;
  t_period = 5000;
  static int i = 0;
  micros_ = micros();
  if (micros_ < t2) return;
  BT_input();
  rec_signal();
  dt = micros() - t0;
  t0 += dt;
  double Dt = double(dt) * 0.000001;
  Acsel = (atan2(AcX, AcZ)) - PI / 2.0;
  Gyro = - (double(GyY) - Nul_compY)  * _1_d_131;

  AcYsum = KF * (AcYsum + Gyro * Dt) + one_KF * Acsel;
  t2 = t0 + t_period;

  if ( flag_crash)
  {
    if ((time_stop_move - 1000) < millis())
    {
      if (abs(AcYsum * RAD_TO_DEG) < 40)
      {
        on_stmot();
      }
      if (time_stop_move  < millis())
      {
        if (abs(AcYsum * RAD_TO_DEG) < 40)
        {
          flag_crash = false;
          counter_stepR = 0;
          counter_stepL = 0;
        }
      }
    }
    counter_stepR = 0;
     counter_stepL = 0;
    return;
  }

  XL = counter_stepL; counter_stepL = 0;
  XR = counter_stepR; counter_stepR = 0;

  double dMoveX = double(XL + XR) * 0.5 / Dt;
  OldCommandSpeed_dMove = OldCommandSpeed;

  dMove = dMoveX - OldCommandSpeed_dMove;
  dMoveOld = dMove;
  Move += (XL + XR) / 2.0 + Dt * ( - OldCommandSpeed);
  double fi = Move/r;
  double dfi = dMove/r;

  Speed = AcYsum * Ka + Gyro * Kda + fi * Kfi + dfi * Kdfi;
  OldCommandSpeed = CommandSpeed / 100.0;
  Speed *= 400.0;

  speed_L = (Speed + Turn);
  speed_R = (Speed - Turn);
  speed_L = constrain(speed_L, -maxSPEED, maxSPEED);
  speed_R = constrain(speed_R, -maxSPEED, maxSPEED);

  SetSpeed(speed_L, speed_R);
  XSpeed = (speed_L + speed_R) / 800.0;
}
