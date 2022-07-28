#include "CarRegulators.h"


extern _Bool ZeroMesFlag;
int16_t Data[4] = {0 , 0, 0, 0};
uint32_t *encoderData[4] = {ENCODER1_CNT, ENCODER2_CNT,ENCODER3_CNT,ENCODER4_CNT};
float Speed_Calc_Car(uint16_t leftWheel, uint16_t rightWheel)
{
    float Speed;
    uint16_t sum = 0;

    Current_Velocity = 0;

    if(rightWheel - leftWheel >= (rightWheel/2)) {leftWheel = 0;} // левый датчик сломан, не учитывается в расчете
    if(leftWheel - rightWheel >= (leftWheel/2)) {rightWheel = 0;}  // правый датчик сломан, не учитывается в расчете

    if(leftWheel == 0 && rightWheel != 0) { sum = rightWheel;}  // учет поломки датчика
    if(rightWheel == 0 && leftWheel != 0) { sum = leftWheel;}   // учет поломки датчика

    if(rightWheel != 0 && leftWheel != 0) { sum = (leftWheel + rightWheel) / 2;}    // все хорошо, берем среднее арифметическое
    Speed = ( sum * StepWheel ) / Freq_Wheel;   // скорость
    Speed = ( Transmission_Flag == R) ? -Speed : Speed;
    RPulseWheel = 0; LPulseWheel = 0;   // обнуление показаний

    if( Speed == Current_Velocity ) { ZeroMesFlag = 1;}
    else {ZeroMesFlag = 0;}
    return Speed;
}

uint32_t leftPeriod, rightPeriod;
int ZeroCounts = 0;
float Speed_Calc_Car_HighFreq(void)
{
    volatile uint32_t P_left, P_right = 0;
    float Speed_Left, Speed_Right, Result = 0.0;
    //LPulseWheel = 0;
    if( LPulseWheel == 0) Speed_Left = 0.0;
    else
    {
        P_left = TIM4->CCR1;
        leftPeriod = P_left;
        Speed_Left = StepHighFreq / (P_left * 0.00002) * 0.33;
       // Speed_l = Speed_Left;
    }

    if( RPulseWheel == 0) Speed_Right = 0.0;
    else
    {
        P_right = TIM3->CCR1;
        rightPeriod = P_right;
        Speed_Right = StepHighFreq / (P_right * 0.00002) * 0.33; // 0.27
       // Speed_r = Speed_Right;
    }

    LPulseWheel = 0; RPulseWheel = 0;

    if( Speed_Left == 0 && Speed_Right == 0) Result = 0.0;
    if( Speed_Left == 0  )  Result = Speed_Right;
    if( Speed_Right == 0 ) Result = Speed_Left;
    if( Speed_Right != 0 && Speed_Left != 0) Result = ((Speed_Left + Speed_Right) / 2);

    Result = (Transmission_Flag == R) ? -Result : Result;

//    if( Result == Current_Velocity ) {ZeroCounts++;}
//    else {ZeroCounts >= 1; ZeroMesFlag = 0;}

    return Result;
}


float Step;
void Speed_Calc_Transmission(void)
{
    for(int i = 0; i <= 1; i++)
    {
        Data[i] = ((int16_t)*encoderData[i]);
        Step = StepTransmission;
        TransmissionReg[i].CurrentSpeed = (((float)(Data[i])) * StepTransmission) / Freq_Timer;
        *encoderData[i] = 0;
    }
}


void PID_Init(void)
{
        TransmissionReg[0].P_k = 0.130;
        TransmissionReg[0].I_k = 0.270;
        TransmissionReg[0].D_k = 0.15;
        TransmissionReg[1].P_k = 0.120;
        TransmissionReg[1].I_k = 0.290;
        TransmissionReg[1].D_k = 0.15;
    for(int i = 0; i <= 1; i++)
    {
        TransmissionReg[i].Error = 0.0;
        TransmissionReg[i].Sum_Error = 0.0;
        TransmissionReg[i].Dif_Error = 0.0;
        TransmissionReg[i].Pred_Error = 0.0;
        TransmissionReg[i].CurrentSpeed = 0.0;
        TransmissionReg[i].TargetSpeed = 0.0;
        TransmissionReg[i].Out = 0.0;
        TransmissionReg[i].MAX_OUT = 1.0;
        TransmissionReg[i].MAX_SUM_ERROR = 6.0;
    }
}

void PID_Calc(Regulator *PID_Calc)
{
        float Out_P, Out_I, Out_D;
        PID_Calc->Error = PID_Calc->TargetSpeed - PID_Calc->CurrentSpeed;
        PID_Calc->Dif_Error = PID_Calc->Error - PID_Calc->Pred_Error;
        Out_P = PID_Calc->Error * PID_Calc->P_k;
        PID_Calc->Pred_Error = PID_Calc->Error;
        PID_Calc->Sum_Error += PID_Calc->Error;
        if( PID_Calc->Sum_Error > PID_Calc->MAX_SUM_ERROR )
        {
            PID_Calc->Sum_Error = PID_Calc->MAX_SUM_ERROR;
        }
        if( PID_Calc->Sum_Error < -PID_Calc->MAX_SUM_ERROR)
        {
            PID_Calc->Sum_Error = -PID_Calc->MAX_SUM_ERROR;
        }
        Out_I = PID_Calc->I_k * PID_Calc->Sum_Error;
        Out_D = PID_Calc->D_k * PID_Calc->Dif_Error;
        PID_Calc->Out = Out_P + Out_I + Out_D;
        if( PID_Calc->Out > PID_Calc->MAX_OUT) { PID_Calc->Out = PID_Calc->MAX_OUT;}
        if( PID_Calc->Out < -PID_Calc->MAX_OUT) { PID_Calc->Out = -PID_Calc->MAX_OUT;}
}
