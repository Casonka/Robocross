#include "CarManagement.h"

// ������� ��������� ������� �������
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
    *   @note CarManagement: < ����� ����������� >
    */
    Transmission_Flag = NONE;
    if( !pin_val(EXTI5_PIN) )   {set_pin(PIN1_12V); Transmission_Flag = N;}
    if( !pin_val(EXTI6_PIN) )   {set_pin(PIN2_12V); Transmission_Flag = R;}
    if( !pin_val(EXTI7_PIN) )   {set_pin(PIN3_12V); Transmission_Flag = F1;}
    if( !pin_val(EXTI8_PIN) )   {set_pin(PIN4_12V); Transmission_Flag = F2;}
    if( !pin_val(EXTI9_PIN) )   {set_pin(PIN5_12V); Transmission_Flag = S1;}
    if( !pin_val(EXTI10_PIN) )  {set_pin(PIN6_12V); Transmission_Flag = S2;}
}


#define SpeedTransmission   0.5     // ����� ����������� �� 6.0
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

void move_transmission_to_certain_state(void)
{
    uint16_t data = adc_data[0];
    //1550 - DOWN
    // 1069 - LEFT
    // 2030 - RIGHT
    // 570 - UP
    if( data > 400 && data < 600)
        {
            MoveTo(UP, 0.5);
    }
    if( data > 1450 && data < 1650)
        {
            MoveTo(DOWN, 0.5);
    }
    if( data > 950 && data < 1150)
        {
            MoveTo(LEFT, 0.5);
    }
    if( data > 1850 && data < 2150)
        {
            MoveTo(RIGHT, 0.5);
        }
    if( data < 350) MoveTo(STOP,0.0);
//    switch(adc_data[0] / 250)
//    {
//        case 2: /// UP (F1 or S1 or S2)
//        //if(pin_val(EXTI7_PIN) && pin_val(EXTI9_PIN) && pin_val(EXTI10_PIN))
//        MoveTo(UP, 0.5);
//       // else
//       // MoveTo(STOP, 0.0);
//        break;
//
//        case 8: /// RIGHT (N or S2)
//        //if(pin_val(EXTI5_PIN) && pin_val(EXTI10_PIN))
//        MoveTo(RIGHT, 0.5);
//        //else
//        //MoveTo(STOP, 0.0);
//        break;
//
//        case 6: /// DOWN (S1 or F2 or R)
//       // if(pin_val(EXTI9_PIN) && pin_val(EXTI8_PIN) && pin_val(EXTI6_PIN))
//        MoveTo(DOWN, 0.5);
//       // else
//       // MoveTo(STOP, 0.0);
//        break;
//
//        case 4: /// LEFT (S1 or N)
//       // if(pin_val(EXTI9_PIN) && pin_val(EXTI5_PIN))
//        MoveTo(LEFT, 0.5);
//        //else
//       // MoveTo(STOP, 0.0);
//        break;
//
//        default:
//        MoveTo(STOP, 0.0);
//    }
}

void Set_Gas(int Pulses)
{
    /*!
    *   @note CarManagement: < ���������� ����� ���������� >
    */
    if (Pulses == WEWE_Speed)  SetPWM(7, -0.5);
    if (Pulses == ZeWE_Speed)  SetPWM(7, 0.5);

    for(int i = 0; i < Pulses; )  // ������ ���
    {
        if(!(TIM9->CR1&0x1)) {TimStart(Tim9); i++;}
    }
    SetPWM(7, 0);
}

void Set_Brake(int state)   // ������
{
    if( state == 0) // ��������� ������ �������
        {
            set_pin(PIN1_12V);
            Brake_Flag = 0;
        }
    else    // ������ ������ �������
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
    *   @note CarManagement: < ������� ������� ���� ��������� >
    */
    int Move_Dir = 1;
    while( Transmission_Flag == NONE)
    {
        Get_Transmission();
        if( Transmission_Flag != NONE ) break;  // ����� ������

        MoveTo(Move_Dir,RecoverySpeed);

        if( TransmissionReg[0].Sum_Error > TriggerErrorValue &&
            TransmissionReg[1].Sum_Error > TriggerErrorValue)
            {
                // �������� �����, ���� �������� �� ��������
                if( Move_Dir == 1) {       TransmissionReg[0].Sum_Error = 0;
                                           TransmissionReg[1].Sum_Error = 0;
                                           Move_Dir = 3; continue;}

                // �������� � ������� ������ �������� � �������, ���� �������� �� ������ ������� �������
                if( Move_Dir == 3) {       TransmissionReg[0].Sum_Error = 0;
                                           TransmissionReg[1].Sum_Error = 0;
                                           Move_Dir = 0; break;}
            }
    }
    if( Transmission_Flag == NONE ) {return;} // �� ������� ����� �� ������ ���������
    if( Transmission_Flag == S1) // ����� S1
        {
            while(Transmission_Flag != N)
            {
                Get_Transmission();
                if( TransmissionReg[0].Sum_Error > TriggerErrorValue &&
                    TransmissionReg[1].Sum_Error > TriggerErrorValue) break;
                MoveTo(4,RecoverySpeed);
            }
        }

    if( Transmission_Flag == S2) // ����� S2
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

    case 1: TransmissionReg[0].TargetSpeed = Speed; TransmissionReg[1].TargetSpeed = Speed;
    break;

    case 2: TransmissionReg[0].TargetSpeed = Speed; TransmissionReg[1].TargetSpeed = -Speed;
    break;

    case 3: TransmissionReg[0].TargetSpeed = -Speed; TransmissionReg[1].TargetSpeed = Speed;
    break;

    case 4: TransmissionReg[0].TargetSpeed = -Speed; TransmissionReg[1].TargetSpeed = -Speed;
    break;
    }
}


