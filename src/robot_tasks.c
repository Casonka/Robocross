#include "robot_tasks.h"

#define TestingTransmission  0
#define TestingClutch        0
#define TestingModBus        0
#define TestingGas           0
#define TestingBrake         0
#define RecoverySector       0

unsigned int ErrorTask;
_Bool ZeroMesFlag;
_Bool StartCarFlag;


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

//xStartHandle
void vStart( void *pvParameters)        // заходит при старте и перезагрузке
{
    StartFlags.StartCarFlag_Brake = 0;
    StartFlags.StartCarFlag_Clutch = 0;
    StartFlags.StartCarFlag_Gas = 0;
    StartFlags.StartCarFlag_ModBus = 0;
    StartFlags.StartCarFlag_Transmission = 0;

    for(;;)
    {
        if( StartCarFlag == 0)
        {
        vTaskPrioritySet(xClutchHandle, 3);  // проверка сцепления
        StartCarFlag = 1;
        vTaskResume(xClutchHandle);

        }


    }
vTaskDelete(NULL);
}

// xClutchHandle
void vClutchManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Управление сцеплением >
    */
    uint8_t status = 1;
    if ( !StartFlags.StartCarFlag_Clutch )
        {
            Get_Clutch();
            if( Clutch_Flag != Full ) Move_Clutch(Full);
            StartFlags.StartCarFlag_Clutch = 1;
            vTaskSuspend(xClutchHandle);
        }
    for(;;)
    {
        if( StartCarFlag == 1)
        {
             switch( status )
            {
              case 1:   // слегка отпустить сцепление
                {
                    Move_Clutch(Back_First);
                    status = 2;
                    vTaskDelay(1000);
                    break;
                }
             case 2: // довести передачу до конца
                {
                    Move_Clutch(Back_Second);
                    status = 3;
                    break;
                }
             default:
                {
                    status = 1;
                    vTaskSuspend(xClutchHandle);
                    break;
                }
            }
        }
    }

// сюда не доходит задача
vTaskDelete(NULL);
}

// xBrakeHandle
void vBrakeManagement ( void *pvParameters)
{
    /*!
    *   @note Управление тормозом
    */
    uint8_t status = 1;
    if ( !StartFlags.StartCarFlag_Brake ) { Move_Clutch(Full); StartFlags.StartCarFlag_Brake = 1; }
    for(;;)
    {
        if( StartFlags.StartCarFlag_Brake ) { vTaskSuspend(xBrakeHandle); }


    }

vTaskDelete(NULL);
}

// xWaitingHangle
void vWaitingEvent( void *pvParameters)    // ждем команду когда все сделано до этого и отправляем скорость (если изменяется)
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
            //ZeroMesFlag = 0; принудительная отправка
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
        if( Velocity > 0) { Get_Transmission(); Set_Transmission(F1); }

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
