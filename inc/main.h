#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
// system files
#include "stm32f4xx.h"      // kernel file for STM32
//-----------------------------------------------------------------
//FreeRTOS files
#include "FreeRTOS.h"       // main FreeRTOS kernel file
#include "FreeRTOSConfig.h" // main configuration file
#include "task.h"           //file for initialization tasks
#include "queue.h"  // работа с очередью переменных
#include "semphr.h" // работа с отложенным прерыванием(семафорами)
#include "croutine.h" // работа с сопрограммами
#include "timers.h" // работа с программными таймерами
//-----------------------------------------------------------------
// custom files
#include "robot_tasks.h"    // tasks list
//#include "Interrupts.h"
//-----------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
