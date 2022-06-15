#include "CarManagement.h"


void Move_Clutch(void)
{
    for(int i = 0; i <= PulseToClutch; )
    {
        if(!(TIM11->CR1&0x1)) {TIM11->CR1|=0x1; i++;}
    }

}
