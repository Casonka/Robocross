    /*!
    *   --------------------------------------------------------------------------
    *                ///Fast Initialization Library Configuration File\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin.
    *   @date 12/06/2022 - last update version FIL STM32
    *
    */

/*!
*   FIL STM32 Driver
*   @file <FilConfig.h>
*   @note This file include driver Fast Initialization Library(FIL) for STM32 controllers
*/

#pragma once
#include <main.h>

// system includes
#include <stdio.h>

#define _DefaultSectorIncludeHandler                2   // access for Basic functions FIL

#define _AdvancedSectorIncludeHandler               1   // access for Advanced functions FIL
#if (_AdvancedSectorIncludeHandler == 1)
    #define _AdvancedCalculatingRCC                 1
    #define _AdvancedGPIOSpecial                    1
    #define _AdvancedCalculatingTimers              1
#endif /*Advanced Sector*/

#define _DeveloperSectorIncludeHandler              1   // access for Developer functions FIL
#if (_DeveloperSectorIncludeHandler == 1)
    #define _DeveloperI2C                           0
    #define _DeveloperCAN                           0
    #define _DeveloperSPI                           0
    #define _DeveloperDAC                           0
    #define _DeveloperDMA                           0
    #define _DeveloperCRYP                          0
    #define _DeveloperRTOS                          1
    #define _DeveloperDeprecatedFunctions           0
    #define _DeveloperModBus                        1
#endif /*Developer Sector*/


/*!
*   Version control
*
*/
#if  !defined(STM32F40_41xxx) && !defined(STM32F401xx)
    #error Not supported on another devices
    #pragma message "Supported devices:"
    #pragma message "STM32F407VGT6, STM32F407VET6"
    #pragma message "STM32F401CCU6"
#endif /*Supporting device securing end*/

#if (_DefaultSectorIncludeHandler != 0 )
    #include "RCC.h"
    #include "GPIO.h"
    #include "TIM.h"
    #include "ADC.h"
    #include "DMA.h"
    #include "USART.h"
    #if (_DefaultSectorIncludeHandler == 1) // Small robot setup
        #include "RCR_PinsBoard.h"
    #endif /*small robot setup*/
    #if (_DefaultSectorIncludeHandler == 2) // Custom setup, none robot
        #include "RCR_Custom.h"
        #include "RCR_SetupCustom.h"
    #endif /*custom setup*/
    #if ((_DefaultSectorIncludeHandler < 0) || (_DefaultSectorIncludeHandler > 2))
        #error Invalid argument of Basic Sector
    #endif /*invalid setup*/
#endif /*_Default setup*/


#if (_DeveloperSectorIncludeHandler == 1)
    #if(_DeveloperRTOS == 1)

//FreeRTOS files
#include "FreeRTOS.h"       // main FreeRTOS kernel file
#include "FreeRTOSConfig.h" // main configuration file
#include "task.h"           //file for initialization tasks
#include "queue.h"  /// работа с очередями
#include "semphr.h" /// работа с отложенным прерыванием(семафорами)
#include "croutine.h" /// работа с сопрограммами
#include "timers.h" /// работа с программными таймерами
#include "event_groups.h" // работа с группами событий

//-----------------------------------------------------------------
// custom files
#include "robot_tasks.h"    // tasks list
//-----------------------------------------------------------------

    #endif /*_DeveloperRTOS*/

    #if(_DeveloperModBus == 1)

    #include "ModBus.h"     ///ModBus ASCII Protocol

    #endif
#endif /*_DeveloperSectorIncludeHandler*/


