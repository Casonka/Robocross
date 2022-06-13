#include "robot_tasks.h"


unsigned int ErrorTask;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void){
/*!
*   @brief vApplicationIdleHook(void) - ������� �����������, ����������� ����� ������������ ����� ����� �� ������
*   @argument nothing - ������� ������ �� �������� � ������ �� ����������
*
*/
}

void vApplicationIdleHook(void)
{

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - ������� ������������, ����������� ����� ���� ������ ������������
*   @argument xTask - ���������� ������, pcTaskName - �������� ������
*
*/
}

void vApplicationMallocFailedHook( void )
{

}

// Tasks functions
//----------------------------------------------------------------------------------------------------------------------
void vInitMainSectors( void *pvParameters)
{
    ErrorTask = 0;
    ModBus_Init();

    vTaskDelete(NULL);
}

void vManagementGearsBox( void *pvParameters )  //car management gears box ( enter code here man!)
{
    for(;;) {

    }
    vTaskDelete(NULL);
}

void vModBusManagement( void *pvParameters )      // UART management: check buffer and parse correct message
{
    for(;;)
    {
        ErrorTask = ModBus_CheckFrame();
        (ErrorTask == 0) ? ModBus_ParsePacket() : ModBus_ClearMsgs();
        //ModBus_Response(UARTReveiver_Flag);
    }
vTaskDelete(NULL);
}

//-------------------------------------------------------------------------------------------------------------------------
