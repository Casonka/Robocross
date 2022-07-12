
#pragma once
#include "FilConfig.h"
uint16_t adc_data[9];

#define Push            1
#define PushOut         0
uint8_t Brake_Flag;  // тормоз
void Set_Brake(int state);

uint8_t Get_Brake(void);

#define PulseToClutch_UP            (13000)
#define PulseToClutch_BackFull      (13000)
#define PulseToClutch_First         (5000)  // 6000
#define PulseToClutch_UPFirst       (7000)
#define PulseToClutch_First_Rev     (5000)
#define PulseToClutch_Second_Rev    (1000)
#define PulseToClutch_Second  ( PulseToClutch_UP - PulseToClutch_First )

#define Full        1
#define Back_First  2
#define Back_Second 3
#define Back_Full   4
#define Forward_First   5
#define Back_First_Rev    6
#define Back_Second_Rev 7
int Clutch_Flag;
void Move_Clutch(int direction); // engine on and moving

void Get_Clutch(void);

#define N   1
#define R   2
#define F1  3
#define F2  4
#define S1  5
#define S2  6
#define NONE 15
int Transmission_Flag;  // флаг передачи
_Bool Set_Transmission(int transmission);    // 2 engines on end move transmission

// направления движения ручки коробки передач
#define UP 3
#define DOWN 2
#define LEFT 4
#define RIGHT 1
#define STOP 0
void move_transmission_to_certain_state(void);


#define Low_Speed         48
#define Zero_Speed        80
#define High_Speed        96
#define WEWE_Speed        32    // c виви осторожно, сделано для фана
#define ZeWE_Speed        33
void Set_Gas(int Pulses);

void Recovery_Transmission(void);

void MoveTo(int direction, float Speed);

void Get_Transmission(void);   // получить данные о состоянии коробки
