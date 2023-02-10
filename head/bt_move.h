uint32_t MOVE_PERIOD = 300;
uint32_t   time_start_move = 0;
const int32_t  MOVSPEED0 = (maxSPEED/100)*3;
const int32_t  MOVSPEED1 = (maxSPEED/100)*5;
const int32_t  MOVSPEED2 = (maxSPEED/100)*10;
const int32_t  MOVSPEED3 = (maxSPEED/100)*15;
const int32_t  MOVSPEED4 = (maxSPEED/100)*20;
const int32_t  MOVSPEED5 = (maxSPEED/100)*25;
const int32_t  MOVSPEED6 = (maxSPEED/100)*30;
const int32_t  MOVSPEED7 = (maxSPEED/100)*35;
const int32_t  MOVSPEED8 = (maxSPEED/100)*40;
const int32_t  MOVSPEED9 = (maxSPEED/100)*45;
const int32_t  MOVSPEED10 = (maxSPEED/100)*50;
int32_t ASPEED = MOVSPEED2;
int32_t DeltaSpeed_100sec = 30000;
bool BT_input()

{
    static char bt_input;
    if (SerialBT.available())
    {
        bt_input = (char)SerialBT.read();
    }
    else
    {
        if(time_start_move < millis())
        {
            if(CommandSpeed>0) CommandSpeed = constrain(CommandSpeed-DeltaSpeed_100sec,0,CommandSpeed);
            if(CommandSpeed<0) CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed,0);
            Turn = 0;
        }
        return false;
    }
    time_start_move = millis() + MOVE_PERIOD;

    switch (bt_input)
    {
        case 'S':
            if(CommandSpeed>0) CommandSpeed = constrain(CommandSpeed-DeltaSpeed_100sec,0,CommandSpeed);
            if(CommandSpeed<0) CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed,0);

            Turn = 0;
            break;
        case 'F':
            Turn = 0;
            CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed, ASPEED);
            break;
        case 'B':
            CommandSpeed = constrain(CommandSpeed-DeltaSpeed_100sec,-ASPEED,CommandSpeed);
            Turn = 0;
            break;
        case 'L':
            Turn = -ASPEED / 2;
            if(CommandSpeed>0) CommandSpeed = constrain(CommandSpeed-DeltaSpeed_100sec,0,CommandSpeed);
            if(CommandSpeed<0) CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed,0);

            break;
        case 'R':
            Turn = ASPEED / 2;
            if(CommandSpeed>0) CommandSpeed = constrain(CommandSpeed-DeltaSpeed_100sec,0,CommandSpeed);
            if(CommandSpeed<0) CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed,0);
            break;
        case 'G':
            CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed, ASPEED);
            Turn = -ASPEED / 2;
            break;
        case 'I':
            CommandSpeed = constrain(CommandSpeed+DeltaSpeed_100sec,CommandSpeed, ASPEED);
            Turn = ASPEED / 2;
            break;

        case 'H':
            break;

        case 'J':
            break;

        case '0':
            ASPEED = MOVSPEED0;
            break;

        case '1':
            ASPEED = MOVSPEED1;
            break;

        case '2':
            ASPEED = MOVSPEED2;
            break;

        case '3':
            ASPEED = MOVSPEED3;
            break;

        case '4':
            ASPEED = MOVSPEED4;
            break;

        case '5':
            ASPEED = MOVSPEED5;
            break;

        case '6':
            ASPEED = MOVSPEED6;
            break;

        case '7':
            ASPEED = MOVSPEED7;
            break;
        case '8':

            ASPEED = MOVSPEED8;
            break;

        case '9':
            ASPEED = MOVSPEED9;
            break;

        case 'q':
            ASPEED = MOVSPEED10;
            break;
        case 'V':
            break;
        case 'v':
            break;
        case 'X':
            break;
        case 'x':
            break;
        default:
            break;
    }
}

