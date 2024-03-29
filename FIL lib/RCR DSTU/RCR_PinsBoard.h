    /*!
    *   --------------------------------------------------------------------------
    *                ///RCR Pin Map File for Small Robot\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin.
    *   @date 20/04/2022 - last update version RCR_PinsBoard.h
    *
    */
#pragma once
#pragma message "Included RCR Small Robot v1.4"

/////////////////////////////////////////////////////////////////////////////
//__________________________________MOTOR PINS_____________________________//
/////////////////////////////////////////////////////////////////////////////
#define MOTOR1_PWM_PIN          pin_id(PORTA,8)

#define MOTOR2_PWM_PIN          pin_id(PORTA,9)

#define MOTOR1_DIR_PIN          pin_id(PORTB,14)

#define MOTOR2_DIR_PIN          pin_id(PORTB,15)

/////////////////////////////////////////////////////////////////////////////
//__________________________________BUTTON PINS_____________________________//
/////////////////////////////////////////////////////////////////////////////
#define BUT1_PIN                pin_id(PORTB,2)

#define BUT2_PIN                pin_id(PORTB,3)

#define BUT3_PIN                pin_id(PORTB,4)

#define BUT4_PIN                pin_id(PORTB,5)

#define BUT5_PIN                pin_id(PORTA,15)

#define POT1_PIN                pin_id(PORTA,4)
/////////////////////////////////////////////////////////////////////////////
//________________________________Encoders_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define ENCODER1A_PIN           pin_id(PORTA,0)

#define ENCODER1B_PIN           pin_id(PORTA,1)

#define ENCODER2A_PIN           pin_id(PORTA,6)

#define ENCODER2B_PIN           pin_id(PORTA,7)

/////////////////////////////////////////////////////////////////////////////
//__________________________________USART__________________________________//
/////////////////////////////////////////////////////////////////////////////
#define USART2_TX_PIN           pin_id(PORTB,6)

#define USART2_RX_PIN           pin_id(PORTB,7)

#define USART3_TX_PIN           pin_id(PORTA,2)

#define USART3_RX_PIN           pin_id(PORTA,3)

/////////////////////////////////////////////////////////////////////////////
//__________________________________I2C____________________________________//
/////////////////////////////////////////////////////////////////////////////
#define SCL_PIN                 pin_id(PORTB,8)

#define SDA_PIN                 pin_id(PORTB,9)

/////////////////////////////////////////////////////////////////////////////
//__________________________________USB____________________________________//
/////////////////////////////////////////////////////////////////////////////
#define USB_PIN-                pin_id(PORTA,11)

#define USB_PIN+                pin_id(PORTA,12)

/////////////////////////////////////////////////////////////////////////////
//__________________________________ADC PINS_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define ADC_TOP_PIN             pin_id(PORTB,0)

#define ADC_BOTTOM_PIN          pin_id(PORTB,1)

#define ADC1_PIN                pin_id(PORTB,10)

#define ADC2_PIN                pin_id(PORTB,12)

#define ADC3_PIN                pin_id(PORTB,13)

/////////////////////////////////////////////////////////////////////////////
//__________________________________OTHER PINS_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define INT_PIN                 pin_id(PORTA,5)

#define LED_PIN                 pin_id(PORTA,10)

#define FREERTOS_LED_PIN        pin_id(PORTC,13)
