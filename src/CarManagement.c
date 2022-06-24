#include "CarManagement.h"

// матрица переходов коробки передач
static uint16_t TransmissionManagementMatrix[4][4] = { 0x00, 0x43, 0x12, 0x13,           // N
                                                       0x21, 0x00, 0x212, 0x213,         // R
                                                       0x34, 0x343, 0x00, 0x33,          // F1
                                                       0x24, 0x243, 0x22, 0x00   };      // F2

void Move_Clutch(int direction)
{
    int Pulses = 0;

    if( direction == Full) {SetPWM(4, 0.5); Pulses = PulseToClutch_UP;}
    else
        {
            SetPWM(4, -0.5);
            if( direction == Back_First) { Pulses = PulseToClutch_First; }
            if( direction == Back_Second) { Pulses = PulseToClutch_Second; }
            if( direction == Back_Full) { Pulses = PulseToClutch_BackFull;}
        }
        for(int i = 0; i < Pulses; )
        {
            if( !pin_val(EXTI3_PIN) && direction == 0) {SetPWM(4, 0); i = Pulses; break;}
            if( !pin_val(EXTI4_PIN) && direction == 1) {SetPWM(4, 0); i = Pulses; break;}
            if(!(TIM11->CR1&0x1)) {TimStart(Tim11); i++;}
        }
    SetPWM(4, 0xFFFF);
}

void Get_Clutch(void)
{
    Clutch_Flag = !pin_val(EXTI3_PIN) ? Back_Second : !pin_val(EXTI4_PIN) ? Full : -1;
}


void Get_Transmission(void)
{
    /*!
    *   @note CarManagement: < флаги трансмиссии >
    */
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
            Get_Transmission();
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


void Set_Gas(int Pulses)
{
    /*!
    *   @note CarManagement: < управление газом автомобиля >
    */
    if (Pulses == WEWE_Speed)  SetPWM(7, -0.5);
    if (Pulses == ZeWE_Speed)  SetPWM(7, 0.5);

    for(int i = 0; i < Pulses; )  // прямой ход
    {
        if(!(TIM9->CR1&0x1)) {TimStart(Tim9); i++;}
    }
    SetPWM(7, 0);
}

void Set_Brake(int state)   // Тормоз
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

uint8_t Get_Brake(void) { Brake_Flag = (pin_out(PIN1_12V)) ? 1 : 0; return Brake_Flag;}

#define RecoverySpeed   1.0
#define TriggerErrorValue   3.0

void Recovery_Transmission(void)
{
    /*!
    *   @note CarManagement: < вернуть коробку если потерялся >
    */
    int Move_Dir = 1;
    while( Transmission_Flag == NONE)
    {
        Get_Transmission();
        if( Transmission_Flag != NONE ) break;  // нашел датчик

        MoveTo(Move_Dir,RecoverySpeed);

        if( TransmissionReg[0].Sum_Error > TriggerErrorValue &&
            TransmissionReg[1].Sum_Error > TriggerErrorValue)
            {
                // движение вверх, если застряли на нейтрали
                if( Move_Dir == 1) {       TransmissionReg[0].Sum_Error = 0;
                                           TransmissionReg[1].Sum_Error = 0;
                                           Move_Dir = 3; continue;}

                // движение в сторону первой передачи и реверса, если застряли на полосе рабочих передач
                if( Move_Dir == 3) {       TransmissionReg[0].Sum_Error = 0;
                                           TransmissionReg[1].Sum_Error = 0;
                                           Move_Dir = 0; break;}
            }
    }
    if( Transmission_Flag == NONE ) {return;} // не удалось выйти на нужное положение
    if( Transmission_Flag == S1) // нашли S1
        {
            while(Transmission_Flag != N)
            {
                Get_Transmission();
                if( TransmissionReg[0].Sum_Error > TriggerErrorValue &&
                    TransmissionReg[1].Sum_Error > TriggerErrorValue) break;
                MoveTo(4,RecoverySpeed);
            }
        }

    if( Transmission_Flag == S2) // нашли S2
        {
            while(Transmission_Flag != N)
            {
                Get_Transmission();
                if( TransmissionReg[0].Sum_Error > TriggerErrorValue &&
                    TransmissionReg[1].Sum_Error > TriggerErrorValue) break;
                MoveTo(1,RecoverySpeed);
            }
        }
    if( Transmission_Flag < 4) {Set_Transmission(N);}
    MoveTo(0,0.0);
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


