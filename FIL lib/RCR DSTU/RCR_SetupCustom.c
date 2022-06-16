#include "RCR_SetupCustom.h"

#define EXTI_RISING_EDGE    1
#define EXTI_FALLING_EDGE   2
#define EXTI_BOTH_EDGES     3

struct
{
    uint32_t Systick;
    uint32_t AHB;
    uint32_t APB1;
    uint32_t APB2;
}Clocks;

void BoardStart(void)
{
    ClocksInit;
    __disable_irq();
    PWR->CR|=PWR_CR_DBP;
    SysTick_Config(168000000);
    Clocks.Systick = current_Systick;
    Clocks.AHB = current_AHB;
    Clocks.APB1 = current_APB1;
    Clocks.APB2 = current_APB2;
    InitPeriph;
    TimPWMConfigure(Tim4,168,100,1,1,1,1);   // 5kHz
    TimEngineClutchConfigure(); // one pulse mode
    TimPIDConfigure(Tim7,8399,1000);    // 10 Hz
    TimEncoderConfigure(Tim8);
    TimEncoderConfigure(Tim1);
    TimEncoderConfigure(Tim3);
    TimEncoderConfigure(Tim2);
    USARTBothConfigure(usart3, 0x222E , 0, 1);
    add_ext_interrupt(EXTI1_PIN, EXTI_RISING_EDGE);    // Hall Sensor 1 - left wheel
    add_ext_interrupt(EXTI2_PIN, EXTI_FALLING_EDGE);    // Hall Sensor 2 - right wheel
    //add_ext_interrupt(EXTI3_PIN, EXTI_RISING_EDGE);     // Clutch Sensor +
    //add_ext_interrupt(EXTI4_PIN, EXTI_RISING_EDGE);     // Clutch Sensor -
    InterruptsEnable();
    __enable_irq();
}

void InterruptsEnable(void)
{
    NVIC_EnableIRQ(TIM7_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
}

void TimEngineClutchConfigure(void)
{
    ConfChannelsTim(Tim11,7,0,0,0,1,0,0,0);
    ConfFreq(Tim11,52,200);
    SetTimOnePulseMode(Tim11,1);
    ConfTimMainOutput(Tim11,1);
    ResetTimCCR1(Tim11);
    SetPWM(4,0xFFFF);
    TimStart(Tim11);
}

void add_ext_interrupt(unsigned char pin, char edge)
{
 SYSCFG->EXTICR [((pin)&0xF) >> 0x02] |= (pin>>4) << ((((pin)&0xF) % 4) << 0x02);
 EXTI->IMR |= (1<<((pin)&0xF));

 switch (edge)
 	{
		case EXTI_FALLING_EDGE:
		  {
		  	 EXTI->FTSR |= (1<<((pin)&0xF));
		  	 EXTI->RTSR &= ~(1<<((pin)&0xF));
        break;
		  }

		case EXTI_RISING_EDGE:
		  {
             EXTI->FTSR &= ~(1<<((pin)&0xF));
		  	 EXTI->RTSR |= (1<<((pin)&0xF));
			 break;
		  }

		case EXTI_BOTH_EDGES:
		  {
		  	 EXTI->RTSR |= (1<<((pin)&0xF));
			 EXTI->FTSR |= (1<<((pin)&0xF));
			 break;
		  }
	}
}
