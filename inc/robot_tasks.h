#pragma once
#include "main.h"

/// FreeRTOS structures

//--------------------------------------------
/// Tasks

xTaskHandle xStartHandle;
void vStart( void *pvParameters);

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
