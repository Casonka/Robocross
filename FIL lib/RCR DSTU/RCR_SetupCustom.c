#include "RCR_SetupCustom.h"

#define EXTI_RISING_EDGE    1
#define EXTI_FALLING_EDGE   2
#define EXTI_BOTH_EDGES     3

void BoardStart(void)
{
    //ResetClock();
    ClocksInit;
    __disable_irq();
    PWR->CR|=PWR_CR_DBP;
    SysTick_Config(168000000);
    InitPeriph;
   TimPWMConfigure(Tim4,168,100,1,1,1,1);   // 5kHz настроить
    TimEngineClutchConfigure();
    TimEncoderConfigure(Tim8);
    TimEncoderConfigure(Tim1);
    TimEncoderConfigure(Tim3);
    TimEncoderConfigure(Tim2);
    TimPIDConfigure(Tim7,8399,1000);    // 5 Hz
    // 14 ћ√ц примерно
    // 2500 - буквы не показывает (примерно 4800 бод)   16% ошибка
    // 2916 - все ок ( почти 4800 бод ) 0.02% ошибка
    // 2187 - все плохо
    // 1458 - вроде ок ( около 9600 бод)  0.02% ошибка
    // 1250 - все плохо
    // 857 - все хорошо ( около 14400 бод )
    // 729 - все хорошо ( около 19200 бод)
    // 121 - все хорошо (около 115200 бод) 0.4% ошибка
    USARTBothConfigure(usart3, 121 , 0, 1);
    add_ext_interrupt(EXTI1_PIN, EXTI_RISING_EDGE);    // Hall Sensor 1 - left wheel
    add_ext_interrupt(EXTI2_PIN, EXTI_FALLING_EDGE);    // Hall Sensor 2 - right wheel
    //add_ext_interrupt(EXTI3_PIN, EXTI_RISING_EDGE);     // Clutch Sensor +
    //add_ext_interrupt(EXTI4_PIN, EXTI_RISING_EDGE);     // Clutch Sensor -
    //add_ext_interrupt(EXTI5_PIN, EXTI_BOTH_EDGES);
    //add_ext_interrupt(EXTI6_PIN, EXTI_BOTH_EDGES);
    //add_ext_interrupt(EXTI7_PIN, EXTI_BOTH_EDGES);
    //add_ext_interrupt(EXTI8_PIN, EXTI_FALLING_EDGE);

    InterruptsEnable();
    __enable_irq();
}

void ResetClock(void)
{
    RCC->PLLCFGR = 0;
    RCC->CFGR = 0;
    RCC->CR = 0;

    RCC->CR |= 0x1000000;
    RCC->PLLCFGR |= 0x11;
    RCC->CFGR |= 0x600000;
    RCC->CFGR |= 0x940A;
}

void InterruptsEnable(void)
{
    NVIC_EnableIRQ(TIM7_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
    //NVIC_EnableIRQ(EXTI3_IRQn);
   // NVIC_EnableIRQ(EXTI4_IRQn);
    //NVIC_EnableIRQ(EXTI9_5_IRQn);
    //NVIC_EnableIRQ(EXTI15_10_IRQn);

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
