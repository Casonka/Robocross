
#pragma once
#include "FilConfig.h"
uint16_t adc_data[8];

int Brake_Flag;  // тормоз
void Set_Brake(int state);

#define PulseToClutch   2778
int Clutch_Flag;
void Move_Clutch(int direction); // engine on and moving

void GetClutch(void);

#define N   0
#define R   1
#define F1  2
#define F2  3
#define S1  4
#define S2  5
#define NONE 15
int Transmission_Flag;  // флаг передачи
_Bool Set_Transmission(int transmission);    // 2 engines on end move transmission

void Set_Gas(int direction, int Pulses);

void Recovery_Transmission(void);

void MoveTo(int direction, float Speed);

void GetTransmission(void);   // получить данные о состоянии коробки
