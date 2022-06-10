#include <FilConfig.h>


//---------------------------------------------------------//
//----------------------USART Interrupts-------------------//
//---------------------------------------------------------//
void USART1_IRQHandler(void) {

USART1->DR = 0x3A;

}



//---------------------------------------------------------//
//----------------------Timer Interrupts-------------------//
//---------------------------------------------------------//
void TIM1_IRQHandler(void) {
ResetTimSR(Tim1);
}

void TIM2_IRQHandler(void) {
ResetTimSR(Tim2);
}

void TIM3_IRQHandler(void) {
ResetTimSR(Tim3);
}

void TIM4_IRQHandler(void) {
ResetTimSR(Tim4);
}

void TIM5_IRQHandler(void) {
ResetTimSR(Tim5);
}

void TIM6_DAC_IRQHandler(void) {    // Custom Regulator
ResetTimSR(Tim6);
}

void TIM7_IRQHandler(void) {    // moving Regulator
ResetTimSR(Tim7);
}

void TIM8_UP_TIM13_IRQHandler(void) {
ResetTimSR(Tim13);
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
