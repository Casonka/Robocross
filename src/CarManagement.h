
#pragma once
#include "FilConfig.h"
uint16_t adc_data[8];

// 0 - ������ ��� ������, �������� ���������
// 1 - ������ ��� ���������, �������� ������
#define Brake_mode      0

#define Push            1
#define PushOut         0
int Brake_Flag;  // ������
void Set_Brake(int state);

#define PulseToClutch_UP   (13000)
#define PulseToClutch_First (5000)
#define PulseToClutch_Second  ( PulseToClutch_UP - PulseToClutch_First )

#define Full        1
#define Back_First  2
#define Back_Second 3
int Clutch_Flag;
void Move_Clutch(int direction); // engine on and moving

void Get_Clutch(void);

#define N   0
#define R   1
#define F1  2
#define F2  3
#define S1  4
#define S2  5
#define NONE 15
int Transmission_Flag;  // ���� ��������
_Bool Set_Transmission(int transmission);    // 2 engines on end move transmission

void Set_Gas(int Pulses);

void Recovery_Transmission(void);

void MoveTo(int direction, float Speed);

void Get_Transmission(void);   // �������� ������ � ��������� �������
