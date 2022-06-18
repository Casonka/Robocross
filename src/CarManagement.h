
#pragma once
#include "FilConfig.h"
uint16_t adc_data[8];


int Brake_Flag;  // тормоз
void Set_Brake(int state);

#define PulseToClutch   2778
int Clutch_Flag;
_Bool Move_Clutch(int direction); // engine on and moving

#define N   0
#define R   -1
#define F1  1
#define F2  2
#define S1  3
#define S2  4
#define NONE -3
int Transmission_Flag;  // флаг передачи
_Bool Set_Transmission(int transmission);    // 2 engines on end move transmission

void Test(int direction, float Speed);

void GetTransmission(void);   // получить данные о состоянии коробки
