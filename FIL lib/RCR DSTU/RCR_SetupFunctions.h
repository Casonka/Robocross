#pragma once

/////////////////////////////////////////////////////////////////////////////
//_____________________________SETUP FUNCTIONS_____________________________//
/////////////////////////////////////////////////////////////////////////////
#define ClocksInit {                                                            \
            set_gpioa;                                                          \
            set_gpiob;                                                          \
            set_gpioc;                                                          \
            set_tim1;                                                           \
            set_tim2;                                                           \
            set_dma2;                                                           \
            set_adc1;                                                           \
            conf_pin(MOTOR1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
            conf_pin(MOTOR2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP); \
            conf_pin(MOTOR1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
            conf_pin(MOTOR2_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);   \
            conf_pin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
            conf_pin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
            conf_pin(ENCODER2A_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
            conf_pin(ENCODER2B_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
            conf_pin(BUT1_PIN, INPUT, PUSH_PULL, LOW_S, NO_PULL_UP);            \
            conf_pin(BUT2_PIN, INPUT, PUSH_PULL, LOW_S, NO_PULL_UP);            \
            conf_pin(BUT3_PIN, INPUT, PUSH_PULL, LOW_S, NO_PULL_UP);            \
            conf_pin(BUT4_PIN, INPUT, PUSH_PULL, LOW_S, NO_PULL_UP);            \
            conf_pin(ADC1_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);          \
            conf_pin(ADC2_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);          \
            conf_pin(ADC3_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);          \
            conf_pin(FREERTOS_LED_PIN, GENERAL, PUSH_PULL, LOW_S, NO_PULL_UP);  }

#define LedInit conf_pin(LED_PIN, GENERAL, PUSH_PULL, LOW_S, NO_PULL_UP)

#define MOTORInit   {   \
            TimPWMConfigure(Tim1}
