
#pragma once
#include <FilConfig.h>


#define MAX_PWM 200


/*!
*   THIS SECTOR FOR NATIVE CODE
*
*/
    void BoardStart(void);

    void TimEngineClutchConfigure(void);

    void add_ext_interrupt(unsigned char pin, char edge);

    void InterruptsEnable(void);

    void ADC_Init(void);

    void SetPWM(unsigned char CHANNEL,float DUTY);

    void TimGasConfigure(void);
/*!
*   END NATIVE CODE
*
*/

#if( _AdvancedCalculatingTimers == 1 )



/*!
*   @brief  SetPWM(CHANNEL, DUTY) - function for management PWMs signals
*       @param  CHANNEL - number of PWM port
*       @param  DUTY - PWM value
*           @note This function have protection about wrong values of PWM
*/



#endif /*_AdvancedCalculatingTimers*/




#define ClocksInit {\
    set_pwr;    \
    set_gpioa;  \
    set_gpiob;  \
    set_gpioc;  \
    set_gpiod;  \
    set_gpioe;  \
    set_tim1;   \
    set_tim2;   \
    set_tim3;   \
    set_tim4;   \
    set_tim5;   \
    set_tim6;   \
    set_tim7;   \
    set_tim8;   \
    set_tim9;   \
    set_tim10;  \
    set_tim11;  \
    set_tim12;  \
    set_tim13;  \
    set_tim14;  \
    set_dma1;   \
    set_dma2;   \
    set_adc1;   \
    set_usart3;\
    set_syscfg;}

#define InitPeriph {\
    conf_pin(BTN1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(BTN2_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN3_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN4_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN5_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN6_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN7_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN8_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN9_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_pin(BTN10_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);  \
    conf_pin(PWM_INHIBIT, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);    \
    conf_pin(PIN1_12V, GENERAL, PUSH_PULL, HIGH_S, NO_PULL_UP);       \
    conf_pin(PIN2_12V, GENERAL, PUSH_PULL, HIGH_S, NO_PULL_UP);       \
    conf_pin(PIN3_12V, GENERAL, PUSH_PULL, HIGH_S, NO_PULL_UP);       \
    conf_pin(PIN4_12V, GENERAL, PUSH_PULL, HIGH_S, NO_PULL_UP);       \
    conf_pin(PIN5_12V, GENERAL, PUSH_PULL, LOW_S, NO_PULL_UP);       \
    conf_pin(PIN6_12V, GENERAL, PUSH_PULL, LOW_S, NO_PULL_UP);       \
    conf_pin(BTN1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_af(BTN1_PWM_PIN, AF2);                                         \
    conf_pin(BTN2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN2_PWM_PIN, AF2);\
    conf_pin(BTN3_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN3_PWM_PIN, AF2);\
    conf_pin(BTN4_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN4_PWM_PIN, AF2);\
    conf_pin(BTN5_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN5_PWM_PIN, AF3);\
    conf_pin(BTN6_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN6_PWM_PIN, AF3);\
    conf_pin(BTN7_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN7_PWM_PIN, AF3);\
    conf_pin(BTN8_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN8_PWM_PIN, AF3);\
    conf_pin(BTN9_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN9_PWM_PIN, AF9);\
    conf_pin(BTN10_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
    conf_af(BTN10_PWM_PIN, AF9);\
    conf_pin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER1A_PIN, AF3);\
    conf_pin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP); \
    conf_af(ENCODER1B_PIN, AF3);\
    conf_pin(ENCODER2A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER2A_PIN, AF1);\
    conf_pin(ENCODER2B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP); \
    conf_af(ENCODER2B_PIN, AF1);\
    conf_pin(ENCODER3A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP); \
    conf_af(ENCODER3A_PIN, AF2);\
    conf_pin(ENCODER3B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP); \
    conf_af(ENCODER3B_PIN, AF2);\
    conf_pin(ENCODER4A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER4A_PIN, AF1);\
    conf_pin(ENCODER4B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP); \
    conf_af(ENCODER4B_PIN, AF1);\
    conf_pin(TX1_PIN, ALTERNATE, PUSH_PULL, LOW_S, NO_PULL_UP);    \
    conf_af(TX1_PIN, AF7);\
    conf_pin(RX1_PIN, ALTERNATE, PUSH_PULL, LOW_S, NO_PULL_UP);   \
    conf_af(RX1_PIN, AF7);\
    conf_pin(GENERAL_PIN_0, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_1, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_2, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_3, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_4, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_5, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_6, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_7, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_8, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(GENERAL_PIN_9, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI1_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI2_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI3_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI4_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI5_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI6_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI7_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI8_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI9_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(EXTI10_PIN, INPUT, PUSH_PULL, FAST_S, PULL_UP);\
    conf_pin(pin_id(PORTA,9), ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(pin_id(PORTA,9), AF8);\
    conf_pin(pin_id(PORTA,10), ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(pin_id(PORTA,10), AF8);\
}

