
#pragma once
#include "main.h"

float Current_Velocity; // ������� ��������

int Brake_Flag;  // ������
void Set_Brake(int state);

#define PulseToClutch   2778
int Clutch_Flag;
_Bool Move_Clutch(int direction); // engine on and moving

#define N   0
#define R   -1
#define F1  1
#define F2  2
int Transmission_Flag;  // ���� ��������
_Bool Set_Transmission(int transmission);    // 2 engines on end move transmission

#define Freq_Timer    0.1      // 10 Hz  1/10 = 0.1 ���
#define StepWheel   0.03665    // ������ �� ���� ��� ������ (48 ��������)
volatile uint16_t LPulseWheel,RPulseWheel;
float Speed_Calc(uint16_t leftWheel, uint16_t rightWheel);

void PI_Init(void);

float PI_Calc(float Speed);
