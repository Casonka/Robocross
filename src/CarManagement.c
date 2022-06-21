#include "CarManagement.h"

// матрица переходов коробки передач
static uint16_t TransmissionManagementMatrix[4][4] = { 0x00, 0x43, 0x12, 0x13,           // N
                                                       0x21, 0x00, 0x212, 0x213,         // R
                                                       0x34, 0x343, 0x00, 0x33,          // F1
                                                       0x24, 0x243, 0x22, 0x00   };      // F2

void Move_Clutch(int direction)
{
    if( direction == 1) {SetPWM(4, 0.5);}
    else { SetPWM(4, -0.5);}

    for(int i = 0; i < PulseToClutch; )
    {
        if( pin_val(EXTI4_PIN) && direction == 0) {SetPWM(4, 0); i = PulseToClutch; break;}
        if( pin_val(EXTI3_PIN) && direction == 1) {SetPWM(4, 0); i = PulseToClutch; break;}
        if(!(TIM11->CR1&0x1)) {TimStart(Tim11); i++;}
    }
    SetPWM(4, 0xFFFF);
    Clutch_Flag = direction == 1 ? 1 : 0;
}

void GetClutch(void)
{
    Clutch_Flag = pin_val(EXTI3_PIN) ? 1 : pin_val(EXTI2_PIN) ? 0 : -1;
}


void GetTransmission(void)
{
    Transmission_Flag = NONE;
    if( !pin_val(EXTI5_PIN) )   {Transmission_Flag = N;}
    if( !pin_val(EXTI6_PIN) )   {Transmission_Flag = R;}
    if( !pin_val(EXTI7_PIN) )   {Transmission_Flag = F1;}
    if( !pin_val(EXTI8_PIN) )   {Transmission_Flag = F2;}
    if( !pin_val(EXTI9_PIN) )   {Transmission_Flag = S1;}
    if( !pin_val(EXTI10_PIN) )  {Transmission_Flag = S2;}
}


#define SpeedTransmission   0.5     // можно увеличивать до 6.0
_Bool Set_Transmission(int transmission)
{
    if( Clutch_Flag == 0 || transmission > 3 || Transmission_Flag > 3) return 0;
    uint16_t Pointers[3];
    if( Transmission_Flag == transmission) {return 1;}
    for(int i = 0; i <= 2; i++)
        { Pointers[i] = (TransmissionManagementMatrix[Transmission_Flag][transmission] >> (8 - (4*i)))&0xF;}
    int Transmission_Flag_begin = Transmission_Flag;
    for(int i = 0; i <= 2; i++)
    {
        while(Pointers[i] != 0)
        {
            GetTransmission();
            MoveTo(Pointers[i], SpeedTransmission);
            if( Transmission_Flag != Transmission_Flag_begin && Transmission_Flag != NONE)
            {
                if(Transmission_Flag == N && i != 2)
                {
                    continue;
                }
                Transmission_Flag_begin = Transmission_Flag;
                Pointers[i] = 0;
            }
        }
    }
    MoveTo(0, 0.00);
    if (Transmission_Flag == NONE) return 0; else return 1;
}

void Set_Gas(int direction, int Pulses)
{
    if( direction == 1) {SetPWM(5, -0.5);}
    else { SetPWM(5, 0.5);}
    for(int i = 0; i < Pulses; )
    {
        if(!(TIM10->CR1&0x1)) {TimStart(Tim10); i++;}
    }
    SetPWM(5, 0);

}

void Set_Brake(int state)   // “ормоз
{
    if( state == 0) // отпустить педаль тормоза
        {
            set_pin(PIN1_12V);
            Brake_Flag = 0;
        }
    else    // нажать педаль тормоза
        {
            reset_pin(PIN1_12V);
            Brake_Flag = 1;
        }
}

void Recovery_Transmission(void)    //попытатьс€ вернуть коробку в нужное положение
{


}

void MoveTo(int direction, float Speed)
{
    switch(direction)
    {
    case 0: TransmissionReg[0].TargetSpeed = 0.0; TransmissionReg[1].TargetSpeed = 0.0;
    break;

    case 1: TransmissionReg[0].TargetSpeed = -Speed; TransmissionReg[1].TargetSpeed = -Speed;
    break;

    case 2: TransmissionReg[0].TargetSpeed = -Speed; TransmissionReg[1].TargetSpeed = Speed;
    break;

    case 3: TransmissionReg[0].TargetSpeed = Speed; TransmissionReg[1].TargetSpeed = -Speed;
    break;

    case 4: TransmissionReg[0].TargetSpeed = Speed; TransmissionReg[1].TargetSpeed = Speed;
    break;
    }
}


