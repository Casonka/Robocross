#pragma once
#include "main.h"

struct
{
    _Bool StartCarFlag_Clutch;
    _Bool StartCarFlag_Brake;
    _Bool StartCarFlag_Transmission;
    _Bool StartCarFlag_ModBus;
    _Bool StartCarFlag_Gas;
    _Bool StartCar_Flag_Main;
    _Bool RestartCar_Flag_Main;
    _Bool StartCarManagement;

}StartFlags;
/// FreeRTOS structures

// старт и перезагрузка
xSemaphoreHandle xStartEvent;

/*!
*   @note xQueue20Handle - очередь скоростей
*/
#define LowGas              1
#define FullSpeed           2
#define _WEWE               3
#define Zero                4
#define HelpTransmission    5
xQueueHandle xQueue20Handle;

/*!
*   @note xQueueBrakeHandle - очередь для тормоза
*/
#define FullStop    1
#define FullOut     2
#define LowBrake    3
#define MiddleBrake 4
#define HighBrake   5
xQueueHandle xQueueBrakeHandle;

/*!
*   @note xQueueTransmissionHandle - очередь команд для передачи
*/
/* те же макросы что и в CarManagement.h*/
xQueueHandle xQueueTransmissionHandle;

//--------------------------------------------
/// Tasks

xTaskHandle xRobotGo;
void vRobotGo( void *pvParameters);

xTaskHandle xStartHandle;
void vStart( void *pvParameters);

xTaskHandle xWaitingHandle;
void vWaitingEvent( void *pvParameters);

xTaskHandle xMailHandle;
void vMessageSending( void * pvParameters);

xTaskHandle xCarManagementHandle;
void vCarManagement( void *pvParameters);

xTaskHandle xCarRegulatorHandle;
void vCarRegulator( void *pvParameters);

xTaskHandle xClutchHandle;
void vClutchManagement( void *pvParameters);

xTaskHandle xBrakeHandle;
void vBrakeManagement( void *pvParameters);

xTaskHandle xGasHandle;
void vGasManagement( void *pvParameters);

xTaskHandle xQueueManagHandle;
void vSecurityMemoryManagement( void *pvParameters);

xTaskHandle xGearsHandle;
void vManagementGearsBox( void *pvParameters);

xTaskHandle xModBusHandle;
void vModBusManagement( void *pvParameters);
//--------------------------------------------
