#include "robot_tasks.h"

#define TestingTransmission  0
#define TestingClutch        0
#define TestingModBus        0
#define TestingGas           0
#define TestingBrake         0
#define RecoverySector       0


/*!
*   @note robot_tasks: < ���� ������ � ������� >
*   0x01 - ������ ��� ������, �� ��������� ������
*   0x02 - ������ ��������� �������
*   0x04 - �� �������� ������
*   0x08 - ������ ��������� ModBus
*   0x10 - ������ � ���������, �� �������� ���� �� ��������
*       0x11 - ������ � ���������, �� �������� ��� �������
*   0x20 - ������ ��� ������� ���������
*/
unsigned int ErrorTask;
_Bool ZeroMesFlag;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{

/*!
*   @brief vApplicationTickHook(void) - ������� �����������, ����������� ����� ������������ ����� ����� �� ������
*   @arg nothing - ������� ������ �� �������� � ������ �� ����������
*
*/
}

void vApplicationIdleHook(void)
{

/*!
*   @brief vApplicationIdleHook(void) - ������� ����������� ����� ������� ���������� ����� ������
*   @arg nothing - ������� ������ �� �������� � ������ �� ����������
*
*/

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - ������� ������������, ����������� ����� ���� ������ ������������
*   @arg xTask - ���������� ������, pcTaskName - �������� ������
*
*/
}

void vApplicationMallocFailedHook( void )
{

}

// Tasks functions
//----------------------------------------------------------------------------------------------------------------------

//xStartHandle
void vStart( void *pvParameters)        // ������� ��� ������ � ������������
{
    StartFlags.StartCarFlag_Brake = 1;
    StartFlags.StartCarFlag_Clutch = 1;
    StartFlags.StartCarFlag_Gas = 1;
    StartFlags.StartCarFlag_ModBus = 0;
    StartFlags.StartCarFlag_Transmission = 0;
    StartFlags.StartCar_Flag_Main = 0;

    for(;;)
    {
        set_pin(PIN2_12V);  // �������� ��� �������������
        vTaskPrioritySet(xBrakeHandle, 3); // ������

        vTaskPrioritySet(xClutchHandle, 3);  // ������ ���������, ���� �� ���� ������

        vTaskSuspend(xModBusHandle);    // ModBus

        vTaskSuspend(xQueueManagHandle);    // ���������� ��������
        vTaskPrioritySet(xQueueManagHandle, 2);

        vTaskSuspend(xWaitingHangle); // ������-������� � �����������
        vTaskPrioritySet(xWaitingHangle, 3);

        reset_pin(PIN2_12V);    // ��������� ���������
        set_pin(PIN3_12V);      // ����� �������� ��������
    }
vTaskDelete(NULL);
}

// xClutchHandle
void vClutchManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� ���������� >
    */
    uint8_t status = 0;

    for(;;)
    {
        if( StartFlags.StartCarFlag_Clutch == 0 ) continue; // ���� ����������, ��� ���� �� ������ ������

             switch( status )
            {
                case 0: // ���������� ���������
                {
                    /*!
                    *   @fixme robot_tasks: �������� ����� ������� ������� ��������� �������
                    */
                     Get_Clutch();
                     if( Clutch_Flag != Full ) Move_Clutch(Full);
                     status = 1;
                     vTaskSuspend(xClutchHandle);   // ��������� ������
                     break;
                }

                case 1: // ��������� ����� �������� ����������
                {
                    status = (Transmission_Flag == F1 || Transmission_Flag == R) ? 2 :
                             (Transmission_Flag == F2 || Transmission_Flag == N) ? 4 : 15;
                    break;
                }

                case 2:   // ������ ��������� ��������� ( � �������� �� ������)
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_First);
                    status = 3;
                    vTaskDelay(1000);
                    break;
                }

                case 3: // ������� �������� �� �����
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_Second);
                    status = 4;
                    break;
                }

                case 4: // ��������� ���������, ��� ��������
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_Second);
                    status = 5;
                    break;
                }

                case 5: // ���������� ��������
                {
                    status = 0;
                    StartFlags.StartCarFlag_Clutch = 0;
                    vTaskSuspend(xClutchHandle);
                    break;
                }

                default: // ���-�� ��������� �� ����������
                {
                    StartFlags.StartCarFlag_Clutch = 0;
                    Get_Transmission();
                    ErrorTask = (Clutch_Flag != Back_Second || Clutch_Flag != Full) ? 0x20 : 0x00;
                    vTaskSuspend(xClutchHandle);
                    break;
                }
            }
    }

// ���� �� ������� ������
vTaskDelete(NULL);
}

// xBrakeHandle
void vBrakeManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� �������� >
    */
    uint8_t status = 1;
    portBASE_TYPE QueueStatus = 0;

    float BrakeMatrixMiddleSpeed[3] = { 3.75, 5.625, 6.75 };    // ������� ���������� ����
    for(;;)
    {
        if( StartFlags.StartCarFlag_Brake == 0) continue;

        switch(status)
        {
            case FullStop: // ������ ������, ������ ��� ������ � ���������
            {
                Set_Brake(Push);
                status = 1;
                vTaskSuspend(xBrakeHandle);
                break;
            }

            case CommandIN: // ������ ������� �� ������
            {
                QueueStatus = xQueueReceive(xQueueBrakeHandle, &status, 100);
                if( QueueStatus == errQUEUE_EMPTY) vTaskSuspend(xBrakeHandle);
                break;
            }

            case LowBrake: // ������ ����������
            {

                break;
            }

            case MiddleBrake: // ������� ����������
            {

                break;
            }

            case HighBrake: // ������� ����������
            {


                break;
            }

            default:  // �������� �� ������
            {


                break;
            }

        }

    }

vTaskDelete(NULL);
}

// xGasHandle
void vGasManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� ����� >
    */

    uint8_t status = _WEWE;

    for(;;)
    {
        if (StartFlags.StartCarFlag_Gas == 0) continue;

        switch(status)
        {
            case _WEWE:
            {
                for(int i = 0; i < 3; i++) { Set_Gas(WEWE_Speed); vTaskDelay(200); Set_Gas(ZeWE_Speed);}
                StartFlags.StartCarFlag_Gas = 0;
                status = 0;
                vTaskSuspend(xGasHandle);
                break;
            }

            case LowGas:
            {
                Set_Gas(Low_Speed);
                break;
            }

            case Zero:
            {
                Set_Gas(Zero_Speed);
                break;
            }

            case HelpTransmission:
            {
                Set_Gas(Low_Speed);
                vTaskDelay(500);
                Set_Gas(Zero_Speed);
            }

        }

    }

vTaskDelete(NULL);
}

// xWaitingHangle
void vWaitingEvent( void *pvParameters)    // ���� ������� ����� ��� ������� �� ����� � ���������� �������� (���� ����������)
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
            //ZeroMesFlag = 0; �������������� ��������
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
        vTaskResume(xQueueManagHandle);
    }
vTaskDelete(NULL);
}

// xQueueManagHandle xQueue20Handle
void vSecurityMemoryManagement ( void *pvParameters) //Queue management: receive value from buffer and send to tasks
{
    /*!
    *   @note robot_tasks: < ���������� �������� �� ������� xQueue20Handle >
    */
    float Velocity;
    const float Vel_Divider = 1.0;
    portBASE_TYPE xStatus;
    for(;;)
    {
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
