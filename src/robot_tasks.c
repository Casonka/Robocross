#include "robot_tasks.h"


unsigned int ErrorTask;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void){
/*!
*   @brief vApplicationIdleHook(void) - функция бездействия, выполняется когда процессорное время ничем не занято
*   @argument nothing - функция ничего не получает и ничего не возвращает
*
*/
}

void vApplicationIdleHook(void)
{

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - функция переполнения, выполняется когда стек задачи переполнился
*   @argument xTask - дескриптор задачи, pcTaskName - название задачи
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
    uint32_t time;
    for(;;)
    {
        time++;
    set_pin(PIN5_12V);
    UARTTransmit_Flag = 1;
//    if( time > 100000)
//    {
//        time = 0;
//        //ModBus_SendResponse("FC");
//    }

    reset_pin(PIN5_12V);
    }
    vTaskDelete(NULL);
}

void vModBusManagement( void *pvParameters )      // UART management: check buffer and parse correct message
{
    unsigned int Data;
    for(;;)
    {
        set_pin(PIN6_12V);
        ErrorTask = ModBus_CheckFrame();
        (ErrorTask == 0) ? Data = ModBus_ParsePacket() : ModBus_ClearMsgs();
        //ModBus_Response(UARTReveiver_Flag);
        xQueueSend(xQueue20Handle, &Data, 0);
        vTaskPrioritySet(xModBusHandle, 1);
        reset_pin(PIN6_12V);
    }
vTaskDelete(NULL);
}

void vSecurityMemoryManagement ( void *pvParameters) //Queue management: receive value from buffer and send to tasks
{

    for(;;)
    {

    }
vTaskDelete(NULL);
}

//-------------------------------------------------------------------------------------------------------------------------
