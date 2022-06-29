#include "robot_tasks.h"

// ������ ������� �������
#define TestingTransmission  1

// ������ ���������
#define TestingClutch        1

// ������ ModBus
#define TestingModBus        0

// ������ ������ ����
#define TestingGas           0

// ������ ������ �������
#define TestingBrake         1

#define MainStart            0

// ������ ���������� ����������
#define RecoverySector       0

// ������ �������������� �������� ��������� �� ModBus
#define ZeroMesFlag_Off      1

/*!
*   @note  !���� ������ � �������
*   0x01 - ������ ��� ������, �� ��������� ������
*   0x02 - ������ ��������� �������
*   0x04 - �� �������� ������
*   0x08 - ������ ��������� ModBus
*   0x10 - ������ � ���������, �� �������� ���� �� ��������
*       0x11 - ������ � ���������, �� �������� ��� �������
*   0x20 - ������ ��� ������� ���������
*   0x40 - �������� � �������������� ��������
*/

unsigned int ErrorTask;

_Bool ZeroMesFlag;
float TargetSpeed;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{
    if( ErrorTask != 0x00) set_pin(PIN2_12V); // �������� ��� ���� �������� � �������
    else reset_pin(PIN2_12V);
    /*!
    *   @brief vApplicationIdleHook(void) - ������� ����������� ����� ������� ���������� ����� ������
    *   @arg nothing - ������� ������ �� �������� � ������ �� ����������
    */
}

void vApplicationIdleHook(void)
{
    /*!
    *   @brief vApplicationTickHook(void) - ������� �����������, ����������� ����� ������������ ����� ����� �� ������
    *   @arg nothing - ������� ������ �� �������� � ������ �� ����������
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

    /* [Reset]     +   [Priority] = [4] */
    /* [Start]     +   [Priority] = [2] */
    /* [Waiting]   +   [Priority] = [3] */
    /* [Mail]      +   [Priority] = [3] */
    /* [Clutch]    +   [Priority] = [3] */
    /* [Brake]     +   [Priority] = [3] */
    /* [Gas]       +   [Priority] = [3] */
    /* [Gear]      +   [Priority] = [3] */
    /* [ModBus]    +   [Priority] = [4] */
    /* [Queue]     +   [Priority] = [3] */

// xRobotGo
void vRobotGo( void *pvParameters)
{
    for(;;)
    {
        xSemaphoreTake(xStartEvent, portMAX_DELAY);

        ModBus_Init();
        PID_Init();
        ErrorTask = 0x00;
        ZeroMesFlag = 0;

        // close active tasks
        vTaskSuspend(xWaitingHandle);
        vTaskSuspend(xMailHandle);
        vTaskSuspend(xGasHandle);
        vTaskSuspend(xBrakeHandle);
        vTaskSuspend(xClutchHandle);
        vTaskSuspend(xGearsHandle);
        vTaskSuspend(xModBusHandle);
        vTaskSuspend(xQueueManagHandle);

        vTaskResume(xStartHandle);
    }

vTaskDelete(NULL);
}

// xStartHandle
void vStart( void *pvParameters)
{
    int once = 0;

    PID_Init();
    ModBus_Init();
    ErrorTask = 0x00;
    ZeroMesFlag = 0;
    UARTTransmit_Flag = 3;

    uint8_t Transmission, Clutch, Brake, Gas;

    for(;;)
    {

        set_pin(PIN3_12V);  // �������� ��� �������������

#if ( TestingBrake == 1)
        Get_Brake();
        vTaskPrioritySet(xBrakeHandle, 3); // ������
        if(Brake_Flag == 1)
        {
            Brake = FullStop;
            xQueueSend(xQueueBrakeHandle, &Brake, 0);
            vTaskResume(xBrakeHandle);
            vTaskDelay(4100);
        }
#endif
#if( TestingClutch == 1)
        Get_Clutch();
        if( Clutch_Flag != Full)
        {
            Clutch = Full;
            xQueueSend(xQueueClutchHandle, &Clutch, 0);
            vTaskPrioritySet(xClutchHandle, 3); // ������ ���������, ���� �� ���� ������
            vTaskResume(xClutchHandle);
            vTaskDelay(3500);
        }
#endif
#if( TestingTransmission == 1)
        Get_Transmission();
        if( Transmission_Flag != N)
        {
            Transmission = N;
            xQueueSend(xQueueTransmissionHandle, &Transmission, 0);
            vTaskPrioritySet(xGearsHandle, 3);  // ������� ������� � ��������
            vTaskResume(xGearsHandle);
            vTaskDelay(6000);
        }
#endif
#if( TestingGas == 1)
        while(!pin_val(GENERAL_PIN_9)) {}
        Gas = _WEWE;
        xQueueSend(xQueueGasHandle, &Gas, 0);
        vTaskPrioritySet(xGasHandle, 3); // �������� ���� (���� ���)
        vTaskResume(xGasHandle);
        vTaskDelay(2000);
#endif
#if( TestingModBus == 1)
        vTaskPrioritySet(xModBusHandle, 4); // ��������� ��������� ModBus
        vTaskResume(xModBusHandle);
#endif

#if( MainStart == 1)
        vTaskPrioritySet(xQueueManagHandle, 3);

        vTaskPrioritySet(xMailHandle, 3);
        vTaskResume(xMailHandle);

        vTaskPrioritySet(xWaitingHandle, 3);
        vTaskResume(xWaitingHandle);

        vTaskResume(xRobotGo); // ����� � ������������ ��� ���������� �������
#endif
        reset_pin(PIN3_12V);    // ��������� ���������
        set_pin(PIN2_12V);      // ����� �������� ��������

        vTaskSuspend(xStartHandle);
    }
vTaskDelete(NULL);
}

// xWaitingHandle
void vWaitingEvent( void *pvParameters)
{
    for(;;)
    {
        if( UART_Buffer[14] != '\0')
        {
            StartFlags.StartCarFlag_ModBus = 1;
            xSemaphoreGive(xUARTEvent);
        }
    }
vTaskDelete(NULL);
}

// xMailHandle
void vMessageSending( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ������������� �������� ��������� >
    */
    portTickType xTimeIncremental;
    xTimeIncremental = xTaskGetTickCount();
    for(;;)
    {
        #if ( ZeroMesFlag_Off == 1)
        ZeroMesFlag = 0;
        #endif
        if( ZeroMesFlag == 0)
        {
            UARTTransmit_Flag = 3;
            ModBus_SendResponseSpeed(Current_Velocity*100);
            Current_Velocity = 0.0;
        }
        vTaskDelayUntil(&xTimeIncremental, ( 100 / portTICK_RATE_MS));  // ����� ����� ������ 100 ��
    }

vTaskDelete(NULL);
}

// xClutchHandle    // xQueueClutchHandle
void vClutchManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� ���������� >
    */
    uint8_t status = 0;

    for(;;)
    {
        if( StartFlags.StartCarFlag_Clutch == 0 ) { vTaskSuspend(xClutchHandle); continue; }
        xQueueReceive(xQueueClutchHandle, &status, portMAX_DELAY);

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
                     StartFlags.StartCar_Flag_Main = 1;
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
                    status = 5;
                    break;
                }

                case 4: // ��������� ���������, ��� ��������
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_Full);
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

// xBrakeHandle // xQueueBrakeHandle
void vBrakeManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� �������� >
    */
    uint8_t status;

    for(;;)
    {
        xQueueReceive(xQueueBrakeHandle, &status, portMAX_DELAY);
        switch(status)
        {

            case errQUEUE_EMPTY:    break;

            case FullStop: // 1
            {
                Set_Brake(Push);
                break;
            }

            case FullOut: // 2
            {
                Set_Brake(PushOut);
                break;
            }

            case LowBrake: // 3
            {
                Set_Brake(Push);
                vTaskDelay(900);
                Set_Brake(PushOut);
                break;
            }

            case MiddleBrake: // 4
            {
                Set_Brake(Push);
                vTaskDelay(1300);
                Set_Brake(PushOut);
                break;
            }

            case HighBrake: // 5
            {
                Set_Brake(Push);
                vTaskDelay(2500);
                Set_Brake(PushOut);
                break;
            }

            case EmergencyBrake: // 6
            {
                Set_Brake(Push);
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
    *       @last �� ������������, �.� �� ������ �� �������������
    */

    uint8_t status = _WEWE;

    for(;;)
    {
        if (StartFlags.StartCarFlag_Gas == 0) vTaskSuspend(xGasHandle);

        switch(status)
        {
            case _WEWE:
            {
                for(int i = 0; i < 3; i++)
                {
                    Set_Gas(WEWE_Speed);
                    vTaskDelay(150);
                    Set_Gas(ZeWE_Speed);
                    vTaskDelay(500);
                }
                StartFlags.StartCar_Flag_Main = 1;
                StartFlags.StartCarFlag_Gas = 0; continue;
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

// xGearsHandle // xQueueTransmissionHandle
void vManagementGearsBox( void *pvParameters )
{
    uint8_t status;
    portBASE_TYPE xStatus;

    for(;;)
    {
        xStatus = xQueueReceive(xQueueTransmissionHandle, &status, portMAX_DELAY);

        switch(status)
        {
            case errQUEUE_EMPTY: break;

            case N:
            {
                while(Clutch_Flag != Full) {}
                Set_Transmission(N);
                break;
            }

            case R:
            {
                while(Clutch_Flag != Full) {}
                Set_Transmission(R);
                break;
            }

            case F1:
            {
                while(Clutch_Flag != Full) {}
                Set_Transmission(F1);
                break;
            }

            case F2:
            {
                while(Clutch_Flag != Full) {}
                Set_Transmission(F2);
                break;
            }

            default:    break;
        }
    }
    vTaskDelete(NULL);
}

// xModBusHandle
void vModBusManagement( void *pvParameters )
{
    float Data;
    for(;;)
    {
        xSemaphoreTake(xUARTEvent, portMAX_DELAY);
        ErrorTask = ModBus_CheckFrame();
        if( ErrorTask == 0x08)
        {
            ModBus_ClearMsgs();
            continue;
        }
        Data = ModBus_ParsePacket();
        ModBus_ClearMsgs();
        if ((Data >= 0.05 || Data <= -0.05) && (Data <= 4.0 || Data >= -4.0 )) {xQueueSend(xQueue20Handle, &Data, 0);}
        else { ErrorTask |= 0x40; continue; }
        ErrorTask &= ~(0x08);

        vTaskResume(xQueueManagHandle);
    }
vTaskDelete(NULL);
}

// xQueueManagHandle
void vSecurityMemoryManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < ���������� �������� �� ������� xQueue20Handle >
    */
    float Speed;
    uint8_t Transmission;
    uint8_t Brake;
    const float Vel_Divider = 1.0;
    portBASE_TYPE xStatus;
    xStatus = pdFALSE;

    for(;;)
    {
        xStatus = xQueueReceive(xQueue20Handle, &Speed, portMAX_DELAY);

        float Divider = Speed - Current_Velocity;

        // ��� ��������� ���������������� �������
        if( Divider < Vel_Divider &&
            Divider > -Vel_Divider && Speed != 0.0 ) { StartFlags.StartCarFlag_ModBus = 0; continue; }

        Get_Transmission();
        /*!
        *   @fixme ����� ����� ������
        */
        Transmission_Flag = N;

        Transmission = NONE;
        Brake = NONE;

        if( Divider < -Vel_Divider) // ���������� ��������
        {
            if( Current_Velocity <= -1.0 && Current_Velocity > -3.333) // ���� � ��������� ����������� ��������
            {
                /*!
                *   @note ����� �� ���� ����� � ��� ������ ��������� �� ���������� ��������, �� ���� ��������� �����
                */
                if( Transmission_Flag != R) Transmission = R;

                Brake = (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Low)) ? FullOut :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Medium)) ? LowBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_High)) ? MiddleBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Emergency)) ? HighBrake : EmergencyBrake;

                StartFlags.StartCarManagement = 1;
            }

            if( Current_Velocity > -1.0 && Current_Velocity <= 1.5 ) // ����� �� ����� ��� ���� ����� ��������
            {
                /*!
                *   @note ����� �� ���� �������� ��� ����� � ������� ��������� �� ���������� ��������
                */
                Transmission = (Speed >= -1.0 && Speed <= 1.0) ? N :
                               (Speed < -1.0) ? R : N;

                Brake = (Speed < -1.0) ? FullOut :
                        (Speed >= -1.0 && Speed <= 1.0) ? HighBrake : EmergencyBrake;
            }

            if( Current_Velocity > 1.0 && Current_Velocity <= 3.333 ) // �������� � ��������� ������ ��������
            {
                /*!
                *   @note ���������� �������� ����� ������ ���� ����� �� ������ ��������
                */
                if( Transmission_Flag != F1) Transmission = F1;

                if( Speed <= 1.5) Transmission = N;

                Brake = ((Speed <= 3.333) && (Speed >= Speed - Brake_Trigger_Low) ) ? FullOut :
                        ((Speed <= 3.333) && (Speed >= Speed - Brake_Trigger_Medium) ) ? LowBrake :
                        ((Speed <= 3.333) && (Speed >= Speed - Brake_Trigger_High) ) ? MiddleBrake :
                        ((Speed <= 3.333) && (Speed >= Speed - Brake_Trigger_Emergency) ) ? HighBrake : EmergencyBrake;
            }

            if( Current_Velocity > 3.333 && Current_Velocity <= 5.0) // �������� � ��������� ������ ��������
            {
                /*!
                *   @note ���������� �������� ����� ������ ���� ����� �� ������ ��������
                */

                if( Transmission != F2) Transmission = F2;

                if( Speed <= 2.778 ) Transmission = F1;

                Brake = ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Low) ) ? FullOut :
                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Medium) ) ? LowBrake :
                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_High) ) ? MiddleBrake :
                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Emergency) ) ? HighBrake : EmergencyBrake;
            }
        }

        if( Divider > Vel_Divider) // ���������� ��������
        {

            if( Current_Velocity < -1.0 && Current_Velocity > -3.333) // ���� � ��������� ����������� ��������
            {
                /*!
                *   @note ������ ��������� � ���������� ��������, �� ���� ����������� �������� � �������� �����
                */
                Transmission = (Speed >= -3.333 && Speed < -1.0) ? R :
                               (Speed >= -1.0 && Speed <= 1.0) ? N : N;

                Brake = (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Low)) ? FullOut :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Medium)) ? LowBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_High)) ? MiddleBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Emergency)) ? HighBrake : EmergencyBrake;
            }

            if( Current_Velocity >= -1.0 && Current_Velocity <= 1.0 ) // ����� �� ����� ��� ���� ����� ��������
            {
                /*!
                *   @note ������ ��������� � ���������, �� �����
                */
                Transmission = (Speed >= -1.0 && Speed <= 1.0) ? N :
                               (Speed > 1.0) ? F1 : N;

                Brake = FullOut;
            }

            if( Current_Velocity > 1.0 && Current_Velocity <= 3.333 ) // �������� � ��������� ������ ��������
            {
                /*!
                *   @note ������ ��������� � ���������� �������� ����� �� ���� �� ������ ��������
                */
                Transmission = ( Speed > 1.0 && Speed <= 4.16667) ? F1 :
                               ( Speed > 4.16667 && Speed <= 5.55) ? F2 : F1;

                Brake = FullOut;
            }

            if( Current_Velocity > 3.333 && Current_Velocity <= 5.0) // �������� � ��������� ������ ��������
            {
                /*!
                *   @note ������� �������. ���� �� ������ � ������ ����������
                */
                Transmission = F2;

                Brake = FullOut;

            }
        }
    xStatus = pdFALSE;
//        if( Transmission == F1) xStatus = xQueueSend(xQueueClutchHandle, &Clutch, 0);
        if( Brake_Flag != Brake)    xStatus = xQueueSend(xQueueBrakeHandle, &Brake, 0);
        if( Transmission != Transmission_Flag)  xStatus = xQueueSend(xQueueTransmissionHandle, &Transmission, 0);
    }
vTaskDelete(NULL);
}

// xTrInit
void vTransmissionInit( void *pvParameters)
{
    /*!
    *   @note ������ ���������� �������� �������
    */
//    portTickType time;
//    time = xTaskGetTickCount();
    for(;;)
    {
        if( Transmission_Flag == N)
        {
            MoveTo(0,0.0);
            vTaskDelay(1000 / portTICK_RATE_MS);
            if( ((adc_data[0] / 250) == LEFT) || ((adc_data[0] / 250) == RIGHT) )
                move_transmission_to_certain_state();
        }
        else move_transmission_to_certain_state();
    }
vTaskDelete(NULL);
}

//-------------------------------------------------------------------------------------------------------------------------
