#pragma once
#include <FilConfig.h>

/// FreeRTOS structures

//--------------------------------------------
/// Tasks

void vInitMainSectors( void *pvParameters);

xQueueHandle xQueue20Handle;
xQueueHandle xQueue21Handle;
xQueueHandle xQueue22Handle;
xTaskHandle xTaskQueueManagHandle;
void vSecurityMemoryManagement( void *pvParameters);

xTaskHandle xGearsHandle;
void vManagementGearsBox(void *pvParameters);

xTaskHandle xModBusHandle;
void vModBusManagement(void *pvParameters);
//--------------------------------------------
