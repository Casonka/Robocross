#include "robot_tasks.h"

// запуск коробки передач
#define TestingTransmission  0

// запуск сцепления
#define TestingClutch        0

// запуск ModBus
#define TestingModBus        1

// запуск педали газа
#define TestingGas           0

// запуск педали тормоза
#define TestingBrake         0

// запуск экстренных алгоритмов
#define RecoverySector       0

// запуск принудительной отправки сообщений по ModBus
#define ZeroMesFlag_Off      1

/*!
*   @note  !Коды ошибок в задачах
*   0x01 - ошибка при старте, не заводится машина
*   0x02 - ошибка положения коробки
*   0x04 - не работает тормоз
*   0x08 - ошибка протокола ModBus
*   0x10 - ошибка в одометрии, не работает один из датчиков
*       0x11 - ошибка в одометрии, не работают оба датчика
*   0x20 - ошибка при отжатии сцепления
*/
unsigned int ErrorTask;

_Bool ZeroMesFlag;
float TargetSpeed;

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{

/*!
*   @brief vApplicationTickHook(void) - функция бездействия, выполняется когда процессорное время ничем не занято
*   @arg nothing - функция ничего не получает и ничего не возвращает
*
*/
}

void vApplicationIdleHook(void)
{

/*!
*   @brief vApplicationIdleHook(void) - функция выполняется после каждого завершения любой задачи
*   @arg nothing - функция ничего не получает и ничего не возвращает
*
*/

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - функция переполнения, выполняется когда стек задачи переполнился
*   @arg xTask - дескриптор задачи, pcTaskName - название задачи
*
*/
}

void vApplicationMallocFailedHook( void )
{

}

// Tasks functions
//----------------------------------------------------------------------------------------------------------------------

// xRobotGo
void vRobotGo( void *pvParameters)
{
    for(;;)
    {
        xSemaphoreTake(xStartEvent, portMAX_DELAY);
        if(StartFlags.StartCar_Flag_Main == 0)    // захват события старта
        {
            StartFlags.StartCar_Flag_Main = 1;
            StartFlags.RestartCar_Flag_Main = 1;
            vTaskResume(xQueueManagHandle);
            vTaskResume(xModBusHandle);
            continue;
        }
        else if(StartFlags.RestartCar_Flag_Main == 1)
        {

            StartFlags.StartCar_Flag_Main = 0;
            StartFlags.RestartCar_Flag_Main = 0;

            // удалить все задачи
            vTaskDelete(xStartHandle);
            vTaskDelete(xClutchHandle);
            vTaskDelete(xBrakeHandle);
            vTaskDelete(xGasHandle);
            vTaskDelete(xGearsHandle);
            vTaskDelete(xModBusHandle);
            vTaskDelete(xCarManagementHandle);
            vTaskDelete(xQueueManagHandle);
            vTaskDelete(xCarRegulatorHandle);

            vQueueDelete(xQueue20Handle);
            vQueueDelete(xQueueBrakeHandle);
            vQueueDelete(xQueueTransmissionHandle);

            // создать снова
            xTaskCreate(vStart, (char *) "START", configMINIMAL_STACK_SIZE, NULL, 2, &xStartHandle);

            xTaskCreate(vClutchManagement, (char *) "CLUTCH", configMINIMAL_STACK_SIZE, NULL, 1, &xClutchHandle);
            vTaskSuspend(xClutchHandle);

            xTaskCreate(vBrakeManagement, (char *) "BRAKE", configMINIMAL_STACK_SIZE, NULL, 1, &xBrakeHandle);
            vTaskSuspend(xBrakeHandle);

            xTaskCreate(vGasManagement, (char *) "GAS", configMINIMAL_STACK_SIZE, NULL, 1, &xGasHandle);
            vTaskSuspend(xGasHandle);

            xTaskCreate(vManagementGearsBox, (char *) "GEAR", configMINIMAL_STACK_SIZE, NULL, 1, &xGearsHandle );
            vTaskSuspend(xGearsHandle);

            xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );
            vTaskSuspend(xModBusHandle);

            xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 1, &xQueueManagHandle );
            vTaskSuspend(xQueueManagHandle);

            xQueue20Handle = xQueueCreate(3, sizeof(float));
            xQueueBrakeHandle = xQueueCreate(3, sizeof(uint8_t));
            xQueueTransmissionHandle = xQueueCreate(3, sizeof(uint8_t));

            if( xQueue20Handle != NULL &&
                xQueueBrakeHandle != NULL &&
                xQueueTransmissionHandle != NULL) { continue; }
        }
    }

vTaskDelete(NULL);
}


// xStartHandle
void vStart( void *pvParameters)
{
    StartFlags.StartCarFlag_Brake = 1;
    StartFlags.StartCarFlag_Clutch = 1;
    StartFlags.StartCarFlag_Gas = 1;
    StartFlags.StartCarFlag_ModBus = 0;
    StartFlags.StartCarManagement = 0;
    StartFlags.StartCarFlag_Transmission = 0;
    StartFlags.StartCar_Flag_Main = 0;
    StartFlags.RestartCar_Flag_Main = 0;

    int once = 0;

    PID_Init();
    ModBus_Init();
    ErrorTask = 0x00;
    ZeroMesFlag = 0;
    TargetSpeed = 0.0;
    UARTTransmit_Flag = 3;

    for(;;)
    {
        if(once == 1)  vTaskSuspend(xStartHandle);

        set_pin(PIN2_12V);  // сообщаем что настраиваемся

#if ( TestingBrake == 1)
        Get_Brake();
        vTaskPrioritySet(xBrakeHandle, 3); // тормоз
        if(Brake_Flag == 1)   { vTaskResume(xBrakeHandle); vTaskDelay(4100); }
#endif
#if( TestingClutch == 1)
        vTaskPrioritySet(xClutchHandle, 3);  // нажать сцепление, если не было нажато
        vTaskResume(xClutchHandle);
#endif
#if( TestingTransmission == 1)

#endif
#if( TestingGas == 1)
        vTaskDelay(1000);
        vTaskPrioritySet(xGasHandle, 3); // проверка газа (виви мод)
        vTaskResume(xGasHandle);
#endif
#if( TestingModBus == 1)
        vTaskDelay(1000);
        vTaskPrioritySet(xModBusHandle, 4);
#endif
        vTaskPrioritySet(xQueueManagHandle, 3);

        vTaskPrioritySet(xMailHandle, 3);
        vTaskResume(xMailHandle);

        vTaskPrioritySet(xWaitingHandle, 3);
        vTaskResume(xWaitingHandle);

        reset_pin(PIN2_12V);    // настройка закончена
        set_pin(PIN3_12V);      // можно начинать движение
        once = 1;
        vTaskResume(xRobotGo);
        // для теста

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
            vTaskSuspend(xMailHandle);
            vTaskResume(xModBusHandle);
        }
    }
vTaskDelete(NULL);
}

// xMailHandle
void vMessageSending( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < периодическая отправка сообщений >
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
        }
        vTaskDelayUntil(&xTimeIncremental, (250 / portTICK_RATE_MS));
    }

vTaskDelete(NULL);
}

// xClutchHandle
void vClutchManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Управление сцеплением >
    */
    uint8_t status = 0;

    for(;;)
    {
        if( StartFlags.StartCarFlag_Clutch == 0 ) continue; // флаг готовности, без него не пойдет дальше

             switch( status )
            {
                case 0: // выжимается сцепление
                {
                    /*!
                    *   @fixme robot_tasks: добавить новую функцию вернуть положение коробки
                    */
                     Get_Clutch();
                     if( Clutch_Flag != Full ) Move_Clutch(Full);
                     status = 1;
                     StartFlags.StartCar_Flag_Main = 1;
                     vTaskSuspend(xClutchHandle);   // сцепление готово
                     break;
                }

                case 1: // проверяем какая передача выставлена
                {
                    status = (Transmission_Flag == F1 || Transmission_Flag == R) ? 2 :
                             (Transmission_Flag == F2 || Transmission_Flag == N) ? 4 : 15;
                    break;
                }

                case 2:   // слегка отпустить сцепление ( с нейтрали на первую)
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_First);
                    status = 3;
                    vTaskDelay(1000);
                    break;
                }

                case 3: // довести передачу до конца
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_Second);
                    status = 5;
                    break;
                }

                case 4: // отпустить полностью, без задержек
                {
                    Get_Clutch();
                    if( Clutch_Flag != Back_Second) Move_Clutch(Back_Full);
                    status = 5;
                    break;
                }

                case 5: // завершение движения
                {
                    status = 0;
                    StartFlags.StartCarFlag_Clutch = 0;
                    vTaskSuspend(xClutchHandle);
                    break;
                }

                default: // что-то произошло со сцеплением
                {
                    StartFlags.StartCarFlag_Clutch = 0;
                    Get_Transmission();
                    ErrorTask = (Clutch_Flag != Back_Second || Clutch_Flag != Full) ? 0x20 : 0x00;
                    vTaskSuspend(xClutchHandle);
                    break;
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
    *   @note robot_tasks: < Управление тормозом >
    */
    uint8_t status = 1;
    for(;;)
    {
        if( StartFlags.StartCarFlag_Brake == 0) vTaskSuspend(xBrakeHandle);

        switch(status)
        {
            case FullStop: // нажать тормоз, только при старте и остановке
            {
                Set_Brake(Push);
                status = 2;
                StartFlags.StartCar_Flag_Main = 1;
                StartFlags.StartCarFlag_Brake = 0; continue;
                break;
            }

            case FullOut:
            {
                Set_Brake(PushOut);
                StartFlags.StartCarFlag_Brake = 0; continue;
                break;
            }

            case LowBrake: // легкое торможение
            {
                Set_Brake(Push);
                vTaskDelay(900);
                Set_Brake(PushOut);
                StartFlags.StartCarFlag_Brake = 0; continue;
                break;
            }

            case MiddleBrake: // среднее торможение
            {
                Set_Brake(Push);
                vTaskDelay(1300);
                Set_Brake(PushOut);
                StartFlags.StartCarFlag_Brake = 0; continue;
                break;
            }

            case HighBrake: // высокое торможение
            {
                Set_Brake(Push);
                vTaskDelay(2500);
                Set_Brake(PushOut);
                StartFlags.StartCarFlag_Brake = 0; continue;
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
    *   @note robot_tasks: < управление газом >
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

// xGearsHandle
void vManagementGearsBox( void *pvParameters )
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
void vModBusManagement( void *pvParameters )
{
    float Data;
    for(;;)
    {
        if (StartFlags.StartCarFlag_ModBus == 0) { vTaskSuspend(xModBusHandle); continue;}
        ErrorTask = ModBus_CheckFrame();
        if( ErrorTask == 0x08)
        {
            ModBus_ClearMsgs();
            StartFlags.StartCarFlag_ModBus = 0;
            continue;
        }
        Data = ModBus_ParsePacket();
        ModBus_ClearMsgs();
        if(Data >= 0.05) {xQueueSend(xQueue20Handle, &Data, 0);}
        else { StartFlags.StartCarFlag_ModBus = 0; continue;}
        ErrorTask = 0;
        vTaskResume(xQueueManagHandle);
        vTaskSuspend(xModBusHandle); continue;
    }
vTaskDelete(NULL);
}

// xCarManagementHandle
void vCarManagement( void *pvParameters)
{

    for(;;)
    {

    }

    vTaskDelete(NULL);
}


// xQueueManagHandle xQueue20Handle xQueueBrakeHandle xQueueTransmissionHandle xQueueGasHandle
void vSecurityMemoryManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Обработчик скорости из очереди xQueue20Handle >
    */
    float Speed;
    uint8_t Transmission;
    uint8_t Brake;
    const float Vel_Divider = 1.0;
    portBASE_TYPE xStatus;
    for(;;)
    {
        if(StartFlags.StartCarFlag_ModBus == 0) vTaskSuspend(xQueueManagHandle);

        // скорость ещё есть, нет необходимости создавать дополнительную очередь
        xStatus = xQueuePeek(xQueue20Handle, &Speed, 0);
        if( xStatus == errQUEUE_EMPTY) {StartFlags.StartCarFlag_ModBus = 0; continue;}

        float Divider = Speed - Current_Velocity;

        // вне диапазона чувствительности системы
        if( Divider < Vel_Divider &&
            Divider > -Vel_Divider && Speed != 0.0 ) { StartFlags.StartCarFlag_ModBus = 0; continue; }

        // требуется повысить скорость
        if( Divider > Vel_Divider)
        {
            StartFlags.StartCarManagement = 1;
            StartFlags.StartCarFlag_Brake = 0;
            StartFlags.StartCarFlag_Gas = 1;
        }

        // требуется понизить скорость
        if( Divider < -Vel_Divider)
        {
            StartFlags.StartCarManagement = 1;
            StartFlags.StartCarFlag_Brake = 1;
            StartFlags.StartCarFlag_Gas = 0;
        }

        // пока разрешаем редактирование передачи и сцепления
        StartFlags.StartCarFlag_Transmission = 1;
        StartFlags.StartCarFlag_Clutch = 1;

        // целевая скорость на уровне второй передачи
        if( Speed >= 4.16667)  { Transmission = F2; }

        // целевая скорость в пределах первой передачи
        if( Speed < 4.1667 && Speed >= Vel_Divider )  { Transmission = F1; }

        if( Speed < -Vel_Divider) { Transmission = R; }

        if( Transmission_Flag == Transmission ) { StartFlags.StartCarFlag_Transmission = 0; } // передача уже стоит
        else
        {
            xStatus = xQueueSend(xQueueTransmissionHandle, &Transmission, 0);

            if( xStatus == errQUEUE_FULL ) { StartFlags.StartCarFlag_Transmission = 0; }
        }

        if (StartFlags.StartCarManagement == 1) { StartFlags.StartCarFlag_ModBus = 0; vTaskResume(xCarManagementHandle); continue; } // передача приоритета исполнителю

    }
vTaskDelete(NULL);
}



//-------------------------------------------------------------------------------------------------------------------------
