#include "CarManagement.h"


_Bool Move_Clutch(int direction)
{
    if( direction == 1) {SetPWM(4, 0.5);}
    else { SetPWM(4, -0.5);}

    for(int i = 0; i <= PulseToClutch; )
    {
        if( pin_val(EXTI3_PIN)) {SetPWM(4, 0); return 1;}
        if(!(TIM11->CR1&0x1)) {TimStart(Tim11); i++;}
    }
    SetPWM(4, 0xFFFF);
return 1;
}

void GetTransmission(void)
{
    if( adc_data[0] > 250 && adc_data[0] <= 600 )   {Transmission_Flag = S1;}
    if( adc_data[0] > 600 && adc_data[0] <= 1000 )   {Transmission_Flag = F2;}
    if( adc_data[0] > 1000 && adc_data[0] <= 1450 )  {Transmission_Flag = F1;}
    if( adc_data[0] > 1450 && adc_data[0] <= 2750 ) {Transmission_Flag = N;}
    if( adc_data[0] > 2750 && adc_data[0] <= 3250 ) {Transmission_Flag = R;}
    if( adc_data[0] > 3250 && adc_data[0] <= 3750)  {Transmission_Flag = S2;}
    if( adc_data[0] <= 250 || adc_data[0] > 3750) {Transmission_Flag = NONE;}
}

_Bool Set_Transmission(int transmission)
{
    if( Clutch_Flag == 0 ) return 0;
    switch(transmission)
    {
        case N:
            {

                return 1;
                break;
            }
        case R:
            {

                return 1;
                break;
            }
        case F1:
            {
                while(Transmission_Flag != 3) { Test(1, 0.2);}
                while(Transmission_Flag != 1) { Test(2, 0.2);}
                return 1;
                break;
            }
        case F2:
            {
                break;
            }
    }
    return 0;
}

void Set_Brake(int state)   // Тормоз
{
    (state == 1) ? set_pin(PIN1_12V) : reset_pin(PIN1_12V);
    Brake_Flag = 1;
}

void GoZero(void)
{

}

void Test(int direction, float Speed)
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


