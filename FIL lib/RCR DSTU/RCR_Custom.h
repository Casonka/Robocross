    /*!
    *   --------------------------------------------------------------------------
    *                ///RCR Pin Map File for Custom Setup\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska.
    *   @date 20/04/2022 - last update version RCR_Custom.h
    *
    */
#pragma once


#if defined(STM32F401xx)

    /*!       @def STM32F401xx - Apply settings for STM32F401CCU6
    *
    *        @note Developer Discovery Board RCR    F401CCU6
    *           @note AHB1 -> GPIOD, DMA2, GPIOB
    *           @note APB1 -> TIM4 ch 4, USART3
    *           @note APB2 -> ADC1, TIM12 ch 1,2
    */

#endif /*Configuration pins for STM32F401xx*/


#if defined(STM32F40_41xxx)

    /*!
    *       @def STM32F40_41xxx - Apply settings for STM32F407VGT6, STM32F407VET6, STM32F411VET6
    *
    *        @note Developer Discovery Board RCR F407VGT6, F407VET6, F411VET6
    *           @note AHB1 -> GPIOD, DMA2, GPIOB
    *           @note APB1 -> TIM4 ch 4, USART3
    *           @note APB2 -> ADC1, TIM12 ch 1,2
    */
/////////////////////////////////////////////////////////////////////////////
//________________________________BTN PWM_______________________________//
/////////////////////////////////////////////////////////////////////////////

#define BTN1_PWM_PIN            pin_id(PORTD,12)       /// TIM4 ch 1  AF2  //   // LefWheel
#define BTN2_PWM_PIN            pin_id(PORTD,13)       /// TIM4 ch 2  AF2  //
#define BTN3_PWM_PIN            pin_id(PORTD,14)       /// TIM4 ch 3  AF2  //   // RightWheel
#define BTN4_PWM_PIN            pin_id(PORTD,15)       /// TIM4 ch 4  AF2  //
#define BTN5_PWM_PIN            pin_id(PORTB,9)        /// TIM11 ch 1 AF3  //
#define BTN6_PWM_PIN            pin_id(PORTB,8)        /// TIM10 ch 1  AF3 //    // Clutch Engine
#define BTN7_PWM_PIN            pin_id(PORTE,6)        /// TIM9  ch 2 AF3  //    // Gas Engine
#define BTN8_PWM_PIN            pin_id(PORTE,5)        /// TIM9  ch 1 AF3  //
#define BTN9_PWM_PIN            pin_id(PORTB,14)       /// TIM12 ch 1 AF9  //    // Engine Gear Box 1
#define BTN10_PWM_PIN           pin_id(PORTB,15)       /// TIM12 ch 2 AF9  //    // Engine Gear Box 2


#define BTN1_CCR                ((uint32_t *)&(TIM4->CCR1))
#define BTN2_CCR                ((uint32_t *)&(TIM4->CCR2))
#define BTN3_CCR                ((uint32_t *)&(TIM4->CCR3))
#define BTN4_CCR                ((uint32_t *)&(TIM4->CCR4))
#define BTN5_CCR                ((uint32_t *)&(TIM11->CCR1))
#define BTN6_CCR                ((uint32_t *)&(TIM10->CCR1))
#define BTN7_CCR                ((uint32_t *)&(TIM9->CCR2))
#define BTN8_CCR                ((uint32_t *)&(TIM9->CCR1))
#define BTN9_CCR                ((uint32_t *)&(TIM12->CCR1))
#define BTN10_CCR               ((uint32_t *)&(TIM12->CCR2))

#define PWM_INHIBIT		pin_id(PORTC,13)       //INHIBIT//

/////////////////////////////////////////////////////////////////////////////
//_____________________________BTN directions___________________________//
/////////////////////////////////////////////////////////////////////////////
#define BTN1_DIR_PIN          pin_id(PORTC,14)          //
#define BTN2_DIR_PIN          pin_id(PORTC,15)          //
#define BTN3_DIR_PIN          pin_id(PORTE,10)          //
#define BTN4_DIR_PIN          pin_id(PORTE,14)          //
#define BTN5_DIR_PIN          pin_id(PORTE,7)           //
#define BTN6_DIR_PIN          pin_id(PORTE,2)           //
#define BTN7_DIR_PIN          pin_id(PORTE,8)           //
#define BTN8_DIR_PIN          pin_id(PORTE,13)          //
#define BTN9_DIR_PIN          pin_id(PORTE,12)          //
#define BTN10_DIR_PIN         pin_id(PORTB,13)          //
/////////////////////////////////////////////////////////////////////////////
//________________________________Encoders_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define ENCODER1A_PIN           pin_id(PORTC,6)          //Энкодер 1 А TIM8//AF3 //синий
#define ENCODER1B_PIN           pin_id(PORTC,7)          //Энкодер 1 B TIM8//AF3 //зеленый
#define ENCODER2A_PIN           pin_id(PORTA,15)         //Энкодер 4 А TIM2//AF1 //синий
#define ENCODER2B_PIN           pin_id(PORTB,3)          //Энкодер 4 B TIM2//AF1 //зеленый
#define ENCODER3A_PIN           pin_id(PORTA,6)          //Энкодер 3 A TIM3//AF2 //синий
#define ENCODER3B_PIN           pin_id(PORTA,7)          //Энкодер 3 А TIM3//AF2 //зеленый
#define ENCODER4A_PIN           pin_id(PORTE,9)          //Энкодер 2 А TIM1//AF1 //синий
#define ENCODER4B_PIN           pin_id(PORTE,11)         //Энкодер 2 B TIM1//AF1 //зеленый



#define  ENCODER1_CNT           ((uint32_t *)&(TIM8->CNT))
#define  ENCODER2_CNT           ((uint32_t *)&(TIM2->CNT))
#define  ENCODER3_CNT           ((uint32_t *)&(TIM3->CNT))
#define  ENCODER4_CNT           ((uint32_t *)&(TIM1->CNT))


/////////////////////////////////////////////////////////////////////////////
//_____________________________GENERAL_PIN_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define GENERAL_PIN_0            pin_id(PORTA,0)                //ADC12_IN0//
#define GENERAL_PIN_1            pin_id(PORTA,1)                //ADC12_IN1//
#define GENERAL_PIN_2            pin_id(PORTA,2)                //ADC12_IN2//
#define GENERAL_PIN_3            pin_id(PORTA,3)                //ADC12_IN3//
#define GENERAL_PIN_4            pin_id(PORTB,0)                //ADC12_IN8//
#define GENERAL_PIN_5            pin_id(PORTB,1)                //ADC12_IN9//
#define GENERAL_PIN_6            pin_id(PORTC,1)                //ADC12_IN11//
#define GENERAL_PIN_7            pin_id(PORTC,2)                //ADC12_IN12//
#define GENERAL_PIN_8            pin_id(PORTC,4)                //ADC12_IN14//
#define GENERAL_PIN_9            pin_id(PORTC,5)                //ADC12_IN15//

/////////////////////////////////////////////////////////////////////////////
//__________________________________USART__________________________________//
/////////////////////////////////////////////////////////////////////////////
//USART3 in stm32, USART1 as PCB header. AF7
#define TX1_PIN                  pin_id(PORTC,10)
#define RX1_PIN                  pin_id(PORTC,11)
//USART1 in stm32, USART2 as PCB header. AF7
#define TX2_PIN                  pin_id(PORTB,6)
#define RX2_PIN                  pin_id(PORTB,7)

#define USB_Switch_ON            pin_id(PORTC,0)
/////////////////////////////////////////////////////////////////////////////
//____________________________External interrupts__________________________//
/////////////////////////////////////////////////////////////////////////////
#define EXTI1_PIN               pin_id(PORTD,0)         // Разъем EXTI1 // HALL_SENSOR_1
#define EXTI2_PIN               pin_id(PORTD,1)         // Разъем EXTI2 // HALL_SENSOR_2
#define EXTI3_PIN               pin_id(PORTD,2)         // Разъем EXTI3 //
#define EXTI4_PIN               pin_id(PORTD,3)         // Разъем EXTI4 //
#define EXTI5_PIN               pin_id(PORTE,4)         // Разъем EXTI5 //
#define EXTI6_PIN               pin_id(PORTD,6)         // Разъем EXTI6 //
#define EXTI7_PIN               pin_id(PORTD,7)         // Разъем EXTI7 //
#define EXTI8_PIN               pin_id(PORTD,8)         // Разъем EXTI8 //
#define EXTI9_PIN               pin_id(PORTD,9)         // Разъем EXTI9 //
#define EXTI10_PIN              pin_id(PORTD,10)        // Разъем EXTI10 //
/////////////////////////////////////////////////////////////////////////////
//________________________________I2C2 pins________________________________//
/////////////////////////////////////////////////////////////////////////////
//I2C2 in stm32; I1,I2 as PCB headers
#define I2C_SDA_PIN             pin_id(PORTB,11)                  //I2C_SDA//
#define I2C_SCL_PIN             pin_id(PORTB,10)                  //I2C_SCL//
/////////////////////////////////////////////////////////////////////////////
//_________________________________+12V_PINS_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define PIN6_12V	        pin_id(PORTB, 4)
#define PIN5_12V	        pin_id(PORTB, 5)
#define PIN4_12V	        pin_id(PORTD, 11)
#define PIN3_12V	        pin_id(PORTA, 5)
#define PIN2_12V	        pin_id(PORTC, 9)
#define PIN1_12V	        pin_id(PORTC, 8)
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//_________________________________Other Pins_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define DYNAMIXEL_IO_CONTROL	        pin_id(PORTB,12)        /// DRUM_DX
/////////////////////////////////////////////////////////////////////////////
#endif /*Configuration pins for STM32F40_41xxx*/

