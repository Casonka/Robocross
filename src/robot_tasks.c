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
            vTaskPrioritySet(xModBusHandle, 2);
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

    for(;;)
    {

    set_pin(PIN5_12V);
    reset_pin(PIN5_12V);
    }
    vTaskDelete(NULL);
}

// xClutchHandle
void vClutchManagement( void *pvPatameters)
{

    for(;;)
    {

    Move_Clutch();


    }
    vTaskDelete(NULL);
}

// xModBusHandle
void vModBusManagement( void *pvParameters )      // UART management: check buffer and parse correct message
{
    unsigned int Data;
    for(;;)
    {
        vTaskPrioritySet(xWaitingHangle, 1);
        set_pin(PIN6_12V);
        ErrorTask = ModBus_CheckFrame();
        (ErrorTask == 0) ? Data = ModBus_ParsePacket() : ModBus_ClearMsgs();
        UARTTransmit_Flag = 1;
        if(ErrorTask == 0) ModBus_SendResponse(":OK\r\n");
        //xQueueSend(xQueue20Handle, &Data, 0);
        ModBus_ClearMsgs();
        ErrorTask = 0;
        reset_pin(PIN6_12V);
        vTaskPrioritySet(xQueueManagHandle, 2);
    }
vTaskDelete(NULL);
}

// xQueueManagHandle
void vSecurityMemoryManagement ( void *pvParameters) //Queue management: receive value from buffer and send to tasks
{
   // int16_t Velocity;

    for(;;)
    {
//    vTaskPrioritySet(xModBusHandle, 1);
//    vTaskPrioritySet(xQueueManagHandle, 1);
//    vTaskPrioritySet(xWaitingHangle, 2);
       // Velocity = xQueueReceive();
    }
vTaskDelete(NULL);
}



//-------------------------------------------------------------------------------------------------------------------------
