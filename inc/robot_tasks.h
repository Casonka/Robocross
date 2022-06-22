#pragma once
#include "main.h"

struct
{
    _Bool StartCarFlag_Clutch;
    _Bool StartCarFlag_Brake;
    _Bool StartCarFlag_Transmission;
    _Bool StartCarFlag_ModBus;
    _Bool StartCarFlag_Gas;

}StartFlags;
/// FreeRTOS structures

//--------------------------------------------
/// Tasks

xTaskHandle xStartHandle;
void vStart( void *pvParameters);

xTaskHandle xClutchHandle;
void vClutchManagement( void *pvParameters);

xTaskHandle xBrakeHandle;
void vBrakeManagement( void *pvParameters);

xTaskHandle xWaitingHangle;
void vWaitingEvent( void *pvParameters);

xQueueHandle xQueue20Handle;
xTaskHandle xQueueManagHandle;
void vSecurityMemoryManagement( void *pvParameters);

xTaskHandle xGearsHandle;
void vManagementGearsBox( void *pvParameters);

xTaskHandle xModBusHandle;
void vModBusManagement( void *pvParameters);
//--------------------------------------------
