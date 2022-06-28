#pragma once

#include "main.h"

typedef struct
{
     float P_k;
     float I_k;
     float D_k;
     float Error;
     float Sum_Error;
     float Dif_Error;
     float Pred_Error;
     float TargetSpeed;
     float CurrentSpeed;
     float MAX_SUM_ERROR;
     float MAX_OUT;
     float Out;

}Regulator;

Regulator TransmissionReg[2];

float Current_Velocity; // текущая скорость

#define Freq_Timer    0.01      // 100 Hz  1/100 = 0.01 сек
#define Freq_Wheel      0.1
#define StepWheel   0.03665    // метров за один шаг колеса (48 магнитов)
#define StepHighFreq  0.1309
volatile uint16_t LPulseWheel,RPulseWheel;
float Speed_Calc_Car(uint16_t leftWheel, uint16_t rightWheel);
float Speed_Calc_Car_HighFreq(void);

#define PI2  6.28314
#define Reduction   92
#define CounterOnOneRotate  85000
#define StepTransmission   ( PI2/CounterOnOneRotate )
void Speed_Calc_Transmission(void);

void PID_Init(void);

void PID_Calc(Regulator *PID_Calc);
