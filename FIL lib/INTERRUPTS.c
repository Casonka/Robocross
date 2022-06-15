
#include <FilConfig.h>

extern unsigned char UART_Buffer[UART_BUFFER_SIZE];
unsigned int status;
volatile uint32_t globalTime;
//---------------------------------------------------------//
//----------------------USART Interrupts-------------------//
//---------------------------------------------------------//
void USART3_IRQHandler(void) {

    while ((USART3->SR & 0x20) >> 5)
             {
             *UARTBufferIndex++ =  USART3->DR;
             if( UARTBufferIndex > UARTBufferEndMsgPointer) {UARTBufferIndex = UARTBufferStartMsgPointer;}
             }
}

//---------------------------------------------------------//
//----------------------Timer Interrupts-------------------//
//---------------------------------------------------------//

void TIM1_IRQHandler(void) {
TIM1->SR = 0;
}

void TIM2_IRQHandler(void) {
TIM2->SR = 0;
}

void TIM3_IRQHandler(void) {
TIM3->SR = 0;
}

void TIM4_IRQHandler(void) {

TIM4->SR = 0;
}

void TIM5_IRQHandler(void) {
TIM5->SR = 0;
}

void TIM6_DAC_IRQHandler(void) {    // Custom Regulator
TIM6->SR = 0;
}

void TIM7_IRQHandler(void) {    // moving Regulator
TIM7->SR = 0;
}

void TIM8_UP_TIM13_IRQHandler(void) {
TIM13->SR = 0;
}

//---------------------------------------------------------//
//----------------------External Interrupts----------------//
//---------------------------------------------------------//

void EXTI0_IRQHandler(void) {
    EXTI->PR=0x1;
}

void EXTI1_IRQHandler(void) {
    EXTI->PR=0x2;
}

void EXTI2_IRQHandler(void) {
  EXTI->PR=0x4;
}

void EXTI3_IRQHandler(void) {
  EXTI->PR=0x8;
}

void EXTI4_IRQHandler(void) {
  EXTI->PR=0x10;
}

void EXTI9_5_IRQHandler(void) {
  if (EXTI->PR&(1<<6))
  {
    EXTI->PR=(1<<6);
  }

  if (EXTI->PR&(1<<7))
  {
    EXTI->PR=(1<<7);
  }

    if (EXTI->PR&(1<<8))
  {
    EXTI->PR=(1<<8);
  }

  if (EXTI->PR&(1<<9))
{
    EXTI->PR=(1<<9);
}
}

void EXTI15_10_IRQHandler(void) {

  if (EXTI->PR&(1<<10))
  {
    EXTI->PR=(1<<10);
  }

}
