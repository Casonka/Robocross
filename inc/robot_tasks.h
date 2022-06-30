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

#define ALL_BITS            (0xFF)
#define Brake_BIT           (1 << 0)
#define Clutch_BIT          (1 << 1)
#define Transmission_BIT    (1 << 2)
EventGroupHandle_t xEventStatus;

// старт и перезагрузка
xSemaphoreHandle xStartEvent;

xSemaphoreHandle xUARTEvent;

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
#define FullStop        1
#define FullOut         2
#define LowBrake        3
#define MiddleBrake     4
#define HighBrake       5
#define EmergencyBrake  6
xQueueHandle xQueueBrakeHandle;

/*!
*   @note xQueueTransmissionHandle - очередь команд для передачи
*/
/* те же макросы что и в CarManagement.h*/
xQueueHandle xQueueTransmissionHandle;


xQueueHandle xQueueClutchHandle;

xQueueHandle xQueueGasHandle;

#define Speed_F1    2.778
#define Speed_F2    4.16667
#define Speed_R     -2.5

#define Brake_Trigger_Low           0.833
#define Brake_Trigger_Medium        1.388
#define Brake_Trigger_High          1.944
#define Brake_Trigger_Emergency     2.5

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

xTaskHandle xTrInit;
void vTransmissionInit( void *pvParameters);

//--------------------------------------------
