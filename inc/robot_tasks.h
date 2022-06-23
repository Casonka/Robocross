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

}StartFlags;
/// FreeRTOS structures

/*!
*   @note xQueue20Handle - ������� ���������
*/
#define LowGas              1
#define FullSpeed           2
#define _WEWE               3
#define Zero                4
#define HelpTransmission    5
xQueueHandle xQueue20Handle;

/*!
*   @note xQueueBrakeHandle - ������� ��� �������
*/
#define FullStop    1
#define CommandIN   2
#define LowBrake    3
#define MiddleBrake 4
#define HighBrake   5
xQueueHandle xQueueBrakeHandle;

/*!
*   @note xQueueTransmissionHandle - ������� ��� ��������
*/
xQueueHandle xQueueTransmissionHandle;
//--------------------------------------------
/// Tasks

xTaskHandle xStartHandle;
void vStart( void *pvParameters);

xTaskHandle xClutchHandle;
void vClutchManagement( void *pvParameters);

xTaskHandle xBrakeHandle;
void vBrakeManagement( void *pvParameters);

xTaskHandle xGasHandle;
void vGasManagement( void *pvParameters);

xTaskHandle xWaitingHangle;
void vWaitingEvent( void *pvParameters);

xTaskHandle xQueueManagHandle;
void vSecurityMemoryManagement( void *pvParameters);

xTaskHandle xGearsHandle;
void vManagementGearsBox( void *pvParameters);

xTaskHandle xModBusHandle;
void vModBusManagement( void *pvParameters);
//--------------------------------------------
