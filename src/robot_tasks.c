#include "robot_tasks.h"


unsigned int ErrorTask;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{
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

// No handle (one step mode)
void vInitMainSectors( void *pvParameters)
{
    ErrorTask = 0;
    PI_Init();
    ModBus_Init();
    vTaskDelete(NULL);
}

// xWaitingHangle
void vWaitingEvent( void *pvParameters)
{
    portBASE_TYPE Tick_begin = xTaskGetTickCount();
    portBASE_TYPE Tick_deadTime;

    for(;;)
    {
        reset_pin(PIN5_12V);
        reset_pin(PIN6_12V);
        set_pin(PIN4_12V);
        if(UART_Buffer[UART_BUFFER_SIZE - 1] != 0)
        {
            reset_pin(PIN4_12V);
            vTaskPrioritySet(xModBusHandle, 3);
        }
        Tick_deadTime = xTaskGetTickCount();
        if( Tick_deadTime - Tick_begin >= 1000 )
        {
                UARTTransmit_Flag = 3;
                ModBus_SendResponse(":D00600-555C0\r\n");
                Tick_begin = Tick_deadTime;
        }

    }
    vTaskDelete(NULL);
}

// xGearsHandle
void vManagementGearsBox( void *pvParameters )  //car management gears box ( enter code here man!)
{
    float Velocity;
    for(;;)
    {
        set_pin(PIN5_12V);
        xQueueReceive(xQueue20Handle, &Velocity, 0);
        reset_pin(PIN5_12V);
    }
    vTaskDelete(NULL);
}


// xModBusHandle
void vModBusManagement( void *pvParameters )      // UART management: check buffer and parse correct message
{
    float Data;
    for(;;)
    {
        set_pin(PIN6_12V);
        ErrorTask = ModBus_CheckFrame();
        (ErrorTask == 0) ? Data = ModBus_ParsePacket() : ModBus_ClearMsgs();
        UARTTransmit_Flag = 1;
        //if(ErrorTask == 0) ModBus_SendResponse(":OK\r\n");
        if(Data != 0.00) {xQueueSend(xQueue20Handle, &Data, 0);}
        ModBus_ClearMsgs();
        ErrorTask = 0;
        reset_pin(PIN6_12V);
        vTaskPrioritySet(xQueueManagHandle, 3);
    }
vTaskDelete(NULL);
}

// xQueueManagHandle
void vSecurityMemoryManagement ( void *pvParameters) //Queue management: receive value from buffer and send to tasks
{
    float Velocity;
    const float Vel_Divider = 1.0;
    portBASE_TYPE xStatus;
    for(;;)
    {
        vTaskPrioritySet(xModBusHandle, 1);
        xStatus = xQueuePeek(xQueue20Handle, &Velocity, 0);
        if( xStatus == pdPASS)
        {
            if( (Velocity - Current_Velocity > Vel_Divider) || (Velocity - Current_Velocity < -Vel_Divider) )
            {
                vTaskPrioritySet(xGearsHandle, 2);
            }
        } else { vTaskPrioritySet(xQueueManagHandle, 1); }
    }
vTaskDelete(NULL);
}



//-------------------------------------------------------------------------------------------------------------------------
