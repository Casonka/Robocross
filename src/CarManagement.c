#include "CarManagement.h"


_Bool Move_Clutch(int direction)
{
    if( direction == 1) {SetPWM(4, 0.5);}
    else { SetPWM(4, -0.5);}

    for(int i = 0; i <= PulseToClutch; )
    {
        if( pin_val(EXTI3_PIN)) {SetPWM(4, 0); return 1;}
        if(!(TIM11->CR1&0x1)) {TimStart(Tim11); i++;}
    }
    SetPWM(4, 0xFFFF);
return 1;
}

_Bool Set_Transmission(int transmission)
{
    if( Clutch_Flag == 0 ) return 0;
    switch(transmission)
    {
        case N:
            {
                if( Clutch_Flag == 1 )  {  }
                return 1;
                break;
            }
        case R:
            {
                if( Clutch_Flag == 1 ) { }
                return 1;
                break;
            }
        case F1:
            {
                if( Clutch_Flag == 1 ) { }
                return 1;
                break;
            }
//        case F2:
//            {
//                break;
//            }
    }
    return 0;
}

void Set_Brake(int state)   // Тормоз
{
    (state == 1) ? set_pin(PIN1_12V) : reset_pin(PIN1_12V);
    Brake_Flag = 1;
}

float Speed_Calc(uint16_t leftWheel, uint16_t rightWheel)
{
    float Speed;
    uint16_t sum = 0;

    Current_Velocity = 0;

    if(rightWheel - leftWheel >= (rightWheel/2)) {leftWheel = 0;} // левый датчик сломан, не учитывается в расчете
    if(leftWheel - rightWheel >= (leftWheel/2)) {rightWheel = 0;}  // правый датчик сломан, не учитывается в расчете

    if(leftWheel == 0 && rightWheel != 0) { sum = rightWheel;}  // учет поломки датчика
    if(rightWheel == 0 && leftWheel != 0) { sum = leftWheel;}   // учет поломки датчика

    if(rightWheel != 0 && leftWheel != 0) { sum = (leftWheel + rightWheel) / 2;}    // все хорошо, берем среднее арифметическое
    Speed = sum * StepWheel / Freq_Timer;   // скорость
    RPulseWheel = 0; LPulseWheel = 0;   // обнуление показаний
    return Speed;
}

static float P_k,I_k;
static float Sum_error,Error;
static float Speed_out;

void PI_Init(void)
{
    P_k = 1.0;
    I_k = 0.0;
    Sum_error = 0.0;
    Error = 0.0;
}

float PI_Calc(float Velocity)
{
    float Err_p, Err_i;
    float Speed_ref = 0.0;
    Error = Velocity - Current_Velocity;

    Err_p = Error * P_k;
    if (Speed_out <= 5.55  && Speed_out >= -5.55)
    {

    }

}

