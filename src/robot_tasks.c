#include "robot_tasks.h"

#define TestingTransmission  0
#define TestingClutch        0
#define TestingModBus        0
#define TestingGas           0

unsigned int ErrorTask;
_Bool ZeroMesFlag;
_Bool StartCarFlag;
// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{
/*!
*   @brief vApplicationIdleHook(void) - функци€ бездействи€, выполн€етс€ когда процессорное врем€ ничем не зан€то
*   @argument nothing - функци€ ничего не получает и ничего не возвращает
*
*/
}

void vApplicationIdleHook(void)
{

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - функци€ переполнени€, выполн€етс€ когда стек задачи переполнилс€
*   @argument xTask - дескриптор задачи, pcTaskName - название задачи
*
*/
}

void vApplicationMallocFailedHook( void )
{

}

// Tasks functions
//----------------------------------------------------------------------------------------------------------------------

//xStartHandle
void vStart( void *pvParameters)        // заходит при старте и перезагрузке
{
    for(;;)
    {
        set_pin(PIN6_12V);
#if (TestingGas == 1)



#endif
#if (TestingTransmission == 1)
             GetTransmission();
            if( Transmission_Flag != N && Transmission_Flag != NONE && Clutch_Flag == 1)
            {
                if( Set_Transmission(N) == N)
                {
                    reset_pin(PIN6_12V);
                    vTaskPrioritySet(xStartHandle, 1);
                    StartCarFlag = 1;
                }
                // попытка вернутьс€ в исходное положение
                else if(Transmission_Flag == NONE) { Recovery_Transmission(); }
            }
#endif
#if (TestingModBus == 1)
            ModBus_Init();
            vTaskPrioritySet(xStartHandle, 1);
#endif
#if (TestingClutch == 1)
             GetClutch();
            if( pin_out(PIN1_12V) ) { Set_Brake(0); }
            if( Clutch_Flag == 0 ) Move_Clutch(1);
#endif
#if (TestingTransmission == 0 && \
     TestingClutch == 0 && \
     TestingModBus == 0 && \
     TestingGas == 0)
        if( !StartCarFlag )
        {
            ModBus_Init();
            PID_Init();
            GetClutch();
            if( pin_out(PIN1_12V) ) { Set_Brake(0); }
            if( Clutch_Flag == 0 ) Move_Clutch(1);
            GetTransmission();
            if( Transmission_Flag != N && Transmission_Flag != NONE && Clutch_Flag == 1)
            {
                if( Set_Transmission(N) == N)
                {
                    reset_pin(PIN6_12V);
                    vTaskPrioritySet(xStartHandle, 1);
                    StartCarFlag = 1;
                }
                // попытка вернутьс€ в исходное положение
                else if(Transmission_Flag == NONE) { Recovery_Transmission(); }
            }
        }
    /*!
    *   @note ≈сли программа проходит этот участок более одного раза, то
    *   возникла проблема с коробкой передач.
    */
        StartCarFlag = 0;
#endif
    }
vTaskDelete(NULL);
}

// xWaitingHangle
void vWaitingEvent( void *pvParameters)    // ждем команду когда все сделано до этого и отправл€ем скорость (если измен€етс€)
{
    portBASE_TYPE Tick_begin = xTaskGetTickCount();
    portBASE_TYPE Tick_deadTime;

    for(;;)
    {
        set_pin(PIN5_12V);
        if(UART_Buffer[UART_BUFFER_SIZE - 1] != 0)
        {

            vTaskPrioritySet(xModBusHandle, 3);
        }
        Tick_deadTime = xTaskGetTickCount();
        if( Tick_deadTime - Tick_begin >= 500 )
        {
            //ZeroMesFlag = 0; принудительна€ отправка
                if(ZeroMesFlag == 0)
                {
                    UARTTransmit_Flag = 3;
                    ModBus_SendResponseSpeed(Current_Velocity*100);
                }
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
        xQueueReceive(xQueue20Handle, &Velocity, 0);
        if( Velocity > 0) { GetTransmission(); Set_Transmission(F1); }

    }
    vTaskDelete(NULL);
}


// xModBusHandle
void vModBusManagement( void *pvParameters )      // UART management: check buffer and parse correct message
{
    float Data;
    for(;;)
    {
        ErrorTask = ModBus_CheckFrame();
        (ErrorTask == 0) ? Data = ModBus_ParsePacket() : ModBus_ClearMsgs();
        UARTTransmit_Flag = 1;
        //if(ErrorTask == 0) ModBus_SendResponse(":OK\r\n");
        if(Data != 0.00) {xQueueSend(xQueue20Handle, &Data, 0);}
        ModBus_ClearMsgs();
        ErrorTask = 0;
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
