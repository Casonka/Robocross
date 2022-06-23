#include "RCR_SetupCustom.h"


#define EXTI_RISING_EDGE    1
#define EXTI_FALLING_EDGE   2
#define EXTI_BOTH_EDGES     3
extern uint16_t adc_data[8];

struct
{
    uint32_t Systick;
    uint32_t AHB;
    uint32_t APB1;
    uint32_t APB2;
}Clocks;

/*!
*   @param DIR_List[10] - List for edit moving direction
*/
   static uint32_t DIR_List[10] = {                           BTN1_DIR_PIN, BTN2_DIR_PIN,
                                                              BTN3_DIR_PIN, BTN4_DIR_PIN,
                                                              BTN5_DIR_PIN, BTN6_DIR_PIN,
                                                              BTN7_DIR_PIN, BTN8_DIR_PIN,
                                                              BTN9_DIR_PIN, BTN10_DIR_PIN };

/*!
*   @param  PWM_List[10] - List for generation PWM signal
*/
   static  uint32_t  *PWM_List[10] =  {                         BTN1_CCR, BTN2_CCR,
                                                                BTN3_CCR, BTN4_CCR,
                                                                BTN5_CCR, BTN6_CCR,
                                                                BTN7_CCR, BTN8_CCR,
                                                                BTN9_CCR, BTN10_CCR };


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
    //ADC_Init();
    TimPWMConfigure(Tim4,83,200,1,1,1,1);   // 5kHz
    TimEngineClutchConfigure(); // one pulse mode
    TimGasConfigure();      // one pulse mode
    TimPIDConfigure(Tim7,8399,1000);    // 10 Hz
    TimPIDConfigure(Tim6,8399,100);    // 100 Hz
    TimPWMConfigure(Tim12,83,200,1,1,0,0);
    TimEncoderConfigure(Tim8);
    TimEncoderConfigure(Tim1);
    TimEncoderConfigure(Tim3);
    TimEncoderConfigure(Tim2);
    USARTBothConfigure(usart3, 0x16C , 0, 1);   //0x16C
    add_ext_interrupt(EXTI1_PIN, EXTI_RISING_EDGE);    // Hall Sensor 1 - left wheel
    add_ext_interrupt(EXTI2_PIN, EXTI_FALLING_EDGE);    // Hall Sensor 2 - right wheel
    //add_ext_interrupt(EXTI3_PIN, EXTI_RISING_EDGE);     // Clutch Sensor +
    //add_ext_interrupt(EXTI4_PIN, EXTI_RISING_EDGE);     // Clutch Sensor -
    InterruptsEnable();
    __enable_irq();
}

void ADC_Init(void)
{
  ADC1->SQR1 |= 8 << 20;
  ADC1->SQR3 |= 0  | (1 << 5)  | (2 << 10)  | (3 << 15) | (8 << 20) | (9 << 25);
  ADC1->SQR2 |= 11| (12 << 5)  | (14 << 10)  | (15 << 15);

  ADC1->SMPR2 |= (7 << 3) | (7 << 6) | (7 << 12) | (7 << 15);
  ADC1->SMPR1 |= (7) | (7 << 3) | (7 << 6) | (7 << 9) | (7 << 24) | (7 << 27);

  ADC1->CR1 |= 0x100 ; //Режим сканирования. Разрешение 12 бит.
  ADC1->CR2 |= 0x302; //Разрешаем использование
  //режима DMA. АЦП будет формировать запрос DMA после каждого преобразования.

  DMA2_Stream0->CR |= 0 << 25;        //Выбираем channel 0
  DMA2_Stream0->PAR |= (uint32_t) &ADC1->DR;//Задаем адрес периферии - регистр результата преобразования АЦП для регулярных каналов.
  DMA2_Stream0->M0AR |= (uint32_t) &adc_data; //Задаем адрес памяти - базовый адрес массива в RAM.
  DMA2_Stream0->CR &= ~DMA_SxCR_DIR; //Направление передачи данных - чтение из периферии, запись в память.
  DMA2_Stream0->NDTR = 8+1; //Количество пересылаемых значений
  DMA2_Stream0->CR &= ~DMA_SxCR_PINC; //Адрес периферии не инкрементируется после каждой пересылки.
  DMA2_Stream0->CR |= DMA_SxCR_MINC|DMA_SxCR_CIRC; //Адрес памяти инкрементируется после каждой пересылки.
  DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0; //Размерность данных периферии - 16 бит.
  DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0; //Размерность данных памяти - 16 бит
  DMA2_Stream0->CR |= DMA_SxCR_PL; //Приоритет - очень высокий (Very High)
  DMA2_Stream0->CR |= DMA_SxCR_TCIE;

  //DMA2->LIFCR = DMA_LIFCR_CTCIF0;
  DMA2_Stream0->CR |= DMA_SxCR_EN | DMA_SxCR_TCIE; //Разрешаем работу канала 1 DMA
  ADC1->CR2 |= ADC_CR2_ADON; //Включаем АЦП
  ADC1->CR2 |= ADC_CR2_SWSTART;
}

void InterruptsEnable(void)
{
    NVIC_EnableIRQ(TIM7_IRQn);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
    NVIC_EnableIRQ(USART3_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
}

void TimEngineClutchConfigure(void)
{
    ConfChannelsTim(Tim11,7,0,0,0,1,0,0,0);
    ConfFreq(Tim11,167,200);        // было раньше 83 200 20.06.2022 хз что это
    SetTimOnePulseMode(Tim11,1);
    ConfTimMainOutput(Tim11,1);
    ResetTimCCR1(Tim11);
    SetPWM(4,0.5);
    TimStart(Tim11);
}

void TimGasConfigure(void)
{
    ConfChannelsTim(Tim9,7,0,0,0,1,0,0,0);
    ConfFreq(Tim9,167,200);
    SetTimOnePulseMode(Tim9,1);
    ConfTimMainOutput(Tim9, 1);
    SetPWM(7,0.5);
    TimStart(Tim9);
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
    void SetPWM(unsigned char CHANNEL,float duty) {
        if (duty > 1)    duty = 1.0;
        if (duty < -1)   duty = -1.0;
        if (duty < 0 )
        {
             *PWM_List[CHANNEL] = ((int32_t)(MAX_PWM +  (duty * MAX_PWM)));
             set_pin(DIR_List[CHANNEL]);
        }
        if (duty >= 0)
        {
             *PWM_List[CHANNEL] = ((int32_t) (duty * MAX_PWM));
             reset_pin(DIR_List[CHANNEL]);
        }
        }
