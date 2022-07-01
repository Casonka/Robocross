#include "robot_tasks.h"

// запуск коробки передач
#define TestingTransmission  1

// запуск сцепления
#define TestingClutch        1

// запуск ModBus
#define TestingModBus        1

// запуск педали газа
#define TestingGas           0

// запуск педали тормоза
#define SynchroClutchDelay   600
#define TestingBrake         1

// запуск работы программы целиком
#define MainStart            1
#define CheckEngine          1

// запуск экстренных алгоритмов
#define RecoverySector       0

#define DEBUG_SUPPORT        0

// запуск принудительной отправки сообщений по ModBus
#define ZeroMesFlag_Off      1

unsigned int ErrorTask;

_Bool ZeroMesFlag;
float TargetSpeed;
_Bool Start = 0;
#if(DEBUG_SUPPORT == 1)
struct
{
    char Transmission;
    char Brake;
    char Clutch;
    char ModBus;

}Debug_Monitor;
#endif

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void)
{
    /*!
    *   @brief vApplicationIdleHook(void) - функция выполняется после каждого завершения любой задачи
    *   @arg nothing - функция ничего не получает и ничего не возвращает
    */

    //if( ErrorTask != 0x00) set_pin(PIN4_12V); // сообщает что есть проблемы в системе
    //else reset_pin(PIN4_12V); // error led pin

}

void vApplicationIdleHook(void)
{
    /*!
    *   @brief vApplicationTickHook(void) - функция бездействия, выполняется когда процессорное время ничем не занято
    *   @arg nothing - функция ничего не получает и ничего не возвращает
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


    /*---------------[OS configuration]-----------*/
    /*--------------------------------------------*/
    /* [Reset]     +   [Priority] = [4]           */
    /* [Start]     +   [Priority] = [2]           */
    /* [Waiting]   +   [Priority] = [3]           */
    /* [Mail]      +   [Priority] = [3]           */
    /* [Clutch]    +   [Priority] = [3]           */
    /* [Brake]     +   [Priority] = [3]           */
    /* [Gas]       +   [Priority] = [3]           */
    /* [Gear]      +   [Priority] = [3]           */
    /* [ModBus]    +   [Priority] = [4]           */
    /* [Queue]     +   [Priority] = [3]           */
    /*--------------------------------------------*/
    /*  [Queue20Handle]           - [Speed]       */
    /*  [QueueBrakeHadnle]        - [Brake]       */
    /*  [QueueGasHandle]          - [Gas]         */
    /*  [QueueTransmissionHandle] - [Transmission]*/
    /*--------------------------------------------*/
    /* xEventStatus - [0000 0000 0000 0000]16 bits*/
    /* Brake_BIT           - [ 0x1 ]              */
    /* Clutch_BIT          - [ 0x2 ]              */
    /* Transmission_BIT    - [ 0x4 ]              */
    /*--------------------------------------------*/

    /*!
    *   @note  !Коды ошибок в задачах
    *   0x01 - ошибка при старте, не заводится машина
    *   0x02 - ошибка положения коробки
    *   0x04 - не работает тормоз
    *   0x08 - ошибка протокола ModBus
    *   0x10 - ошибка в одометрии, не работает один из датчиков
    *   0x20 - ошибка в одометрии, не работают оба датчика
    *   0x40 - ошибка при отжатии сцепления
    *   0x80 - проблемы с инициализацией скорости
    */

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

    EventBits_t xEventBits;

    uint8_t Transmission, Clutch, Brake, Gas;
#if(DEBUG_SUPPORT == 1)
    Debug_Monitor.Clutch = '0';
    Debug_Monitor.Brake = '0';
    Debug_Monitor.ModBus = '0';
    Debug_Monitor.Transmission = '0';
#endif

    for(;;)
    {
        set_pin(PIN3_12V);  // сообщаем что настраиваемся

        // очистка группы событий
        xEventBits = xEventGroupClearBits(xEventStatus, ALL_BITS);

        set_pin(PIN1_12V); // тормоз вкл

#if ( TestingBrake == 1)
        Get_Brake();
        vTaskPrioritySet(xBrakeHandle, 3); // тормоз
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
            Clutch = 0;
            xQueueSend(xQueueClutchHandle, &Clutch, 0);
            vTaskPrioritySet(xClutchHandle, 3); // нажать сцепление, если не было нажато
            vTaskResume(xClutchHandle);
            vTaskDelay(3500);
        }
#endif
#if( TestingTransmission == 1)
        Get_Transmission();
        vTaskPrioritySet(xGearsHandle, 3);  // вернуть коробку в нейтраль
        if( Transmission_Flag != N)
        {
            Clutch_Flag = Full;
            Transmission = N;
            xQueueSend(xQueueTransmissionHandle, &Transmission, 0);
        }
        xEventBits = xEventGroupClearBits(xEventStatus, Transmission_BIT);
        vTaskResume(xGearsHandle);
        vTaskDelay(3000);
#endif
#if( TestingGas == 1)
        while(!pin_val(GENERAL_PIN_9)) {}
        Gas = _WEWE;
        xQueueSend(xQueueGasHandle, &Gas, 0);
        vTaskPrioritySet(xGasHandle, 3); // проверка газа (виви мод)
        vTaskResume(xGasHandle);
        vTaskDelay(2000);
#endif
#if( TestingModBus == 1)
        vTaskPrioritySet(xModBusHandle, 4); // включение протокола ModBus
        vTaskResume(xModBusHandle);
#endif

#if( MainStart == 1)

#if( CheckEngine == 1)
        set_pin(PIN4_12V); // внимание
        while(!pin_val(GENERAL_PIN_9)) {}
        vTaskDelay(1000);
        reset_pin(PIN4_12V);    // настройка закончена
        while(pin_val(GENERAL_PIN_8)) {}
        set_pin(PIN2_12V);      // можно начинать движение
        reset_pin(PIN3_12V);
#endif
        vTaskPrioritySet(xQueueManagHandle, 3);

        vTaskPrioritySet(xMailHandle, 3);
        vTaskResume(xMailHandle);

        vTaskPrioritySet(xWaitingHandle, 3);
        vTaskResume(xWaitingHandle);


        //vTaskResume(xRobotGo); // сброс и перезагрузка при отключении питания
#endif

        vTaskSuspend(xStartHandle);
    }
vTaskDelete(NULL);
}

// xWaitingHandle
void vWaitingEvent( void *pvParameters)
{
    uint32_t deadtime = 0xFFFFFFFF;
    for(;;)
    {
        if( UART_Buffer[14] != '\0')
        {
            StartFlags.StartCarFlag_ModBus = 1;
            xSemaphoreGive(xUARTEvent);
        }
        else { deadtime--; }
        if( deadtime <= 5) { ModBus_Init(); }
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
            Current_Velocity = 0.0;
        }
        vTaskDelayUntil(&xTimeIncremental, ( 100 / portTICK_RATE_MS));  // Гарри хочет каждый 100 мс
    }

vTaskDelete(NULL);
}

// xClutchHandle    // xQueueClutchHandle
void vClutchManagement( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Управление сцеплением >
    */
    uint8_t status = 1;
    EventBits_t xEvents;
    portBASE_TYPE xStatus = 0;

    for(;;)
    {
        xQueueReceive(xQueueClutchHandle, &status, portMAX_DELAY);

             switch( status )
            {
                case 0: // выжимается сцепление
                {
                     Get_Clutch();
                     if( Clutch_Flag != Full )
                     {
                         Move_Clutch(Full);
                         xEvents = xEventGroupSetBits(xEventStatus, Clutch_BIT);
                     }
                     break;
                }

                case 1: // проверяем какая передача выставлена
                {
                    xEvents = xEventGroupWaitBits(xEventStatus, Transmission_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
                    status = (Transmission_Flag == F1 || Transmission_Flag == R) ? 2 :
                             (Transmission_Flag == F2 || Transmission_Flag == N) ? 4 : 15;
                }

                case 2:   // слегка отпустить сцепление ( с нейтрали на первую)
                {
                    vTaskDelay(3000);
                    Move_Clutch(Back_First);
                    status = 3;
                    vTaskDelay(1000);
                }

                case 3: // довести передачу до конца
                {
                    set_pin(PIN3_12V);
                    Move_Clutch(Back_Second);
                    break;
                }

                case 4: // отпустить полностью, без задержек
                {
                    Move_Clutch(Back_Full);
                    xEvents = xEventGroupClearBits(xEventStatus, Clutch_BIT);
                    break;
                }

                default: // что-то произошло с коробкой
                {
                    Get_Transmission();
                    ErrorTask = (Clutch_Flag != Back_Second || Clutch_Flag != Full) ? 0x40 : 0x00;
                    break;
                }
            }
    }

// сюда не доходит задача
vTaskDelete(NULL);
}

// xBrakeHandle // xQueueBrakeHandle
void vBrakeManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Управление тормозом >
    */
    uint8_t status;
    EventBits_t xEvent;

    for(;;)
    {
        xQueueReceive(xQueueBrakeHandle, &status, portMAX_DELAY);
#if(DEBUG_SUPPORT == 1)
        Debug_Monitor.Brake = 'Y';
#endif
        switch(status)
        {
            case errQUEUE_EMPTY:    break;

            case FullStop: // 1
            {
                xEvent = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                Set_Brake(Push);
                xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
                break;
            }

            case FullOut: // 2
            {
                Set_Brake(PushOut);
                //xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
                break;
            }

            case LowBrake: // 3
            {
                Set_Brake(Push);
                vTaskDelay(900);
                Set_Brake(PushOut);
                xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
                break;
            }

            case MiddleBrake: // 4
            {
                xEvent = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                vTaskDelay(SynchroClutchDelay);
                Set_Brake(Push);
                vTaskDelay(1300);
                Set_Brake(PushOut);
                xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
                break;
            }

            case HighBrake: // 5
            {
                xEvent = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                vTaskDelay(SynchroClutchDelay);
                Set_Brake(Push);
                vTaskDelay(2500);
                Set_Brake(PushOut);
                xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
                break;
            }

            case EmergencyBrake: // 6
            {
                Set_Brake(Push);
                xEvent = xEventGroupSetBits(xEventStatus, Brake_BIT);
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
    *       @last не используется, т.к на вторую не переключаемся
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
    EventBits_t xEvents;

    for(;;)
    {
        xStatus = xQueueReceive(xQueueTransmissionHandle, &status, portMAX_DELAY);

        switch(status)
        {
            case errQUEUE_EMPTY: break;

            case N:
            {
                xEvents = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                Set_Transmission(N);
                xEvents = xEventGroupSetBits(xEventStatus, Transmission_BIT);
                break;
            }

            case R:
            {
                xEvents = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                Set_Transmission(R);
                xEvents = xEventGroupSetBits(xEventStatus, Transmission_BIT);
                break;
            }

            case F1:
            {
                xEvents = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                Set_Transmission(F1);
                xEvents = xEventGroupSetBits(xEventStatus, Transmission_BIT);
                break;
            }

            case F2:
            {
                xEvents = xEventGroupWaitBits(xEventStatus, Clutch_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
                Set_Transmission(F2);
                xEvents = xEventGroupSetBits(xEventStatus, Transmission_BIT);
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
       // set_pin(PIN3_12V);
        if( ErrorTask == 0x08)
        {
            ModBus_ClearMsgs();
            continue;
        }
        Data = ModBus_ParsePacket();
        ModBus_ClearMsgs();
        if (Data <= 4.0 || Data >= -4.0 ) {xQueueSend(xQueue20Handle, &Data, 0);}
        else { ErrorTask = 0x40; continue; }
        ErrorTask = 0;

        vTaskResume(xQueueManagHandle);
    }
vTaskDelete(NULL);
}

// xQueueManagHandle
void vSecurityMemoryManagement ( void *pvParameters)
{
    /*!
    *   @note robot_tasks: < Обработчик скорости из очереди xQueue20Handle >
    */
    float Speed;
    uint8_t Transmission;
    uint8_t Brake;
    uint8_t Clutch = NONE;
    const float Vel_Divider = 0.5;

    portBASE_TYPE xStatus;
    xStatus = pdFALSE;
    EventBits_t xEvent;

    for(;;)
    {
        xStatus = xQueueReceive(xQueue20Handle, &Speed, portMAX_DELAY);
       // set_pin(PIN4_12V);
        float Divider = Speed - Current_Velocity;

        // вне диапазона чувствительности системы
        if( Divider < Vel_Divider &&
            Divider > -Vel_Divider && Speed != 0.0 )  continue;

        Transmission = NONE;
        Brake = NONE;
        Clutch = NONE;

        if( Divider < -Vel_Divider) // уменьшение скорости
        {
            if( Current_Velocity <= -1.0 && Current_Velocity > -3.333) // едем в диапазоне реверсивной передачи
            {
                /*!
                *   @note Здесь мы едем назад и нам пришло сообщение об уменьшении скорости, то есть ускорении назад
                */
                if( Transmission_Flag != R) Transmission = R;

                Brake = (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Low)) ? FullOut :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Medium)) ? LowBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_High)) ? MiddleBrake :
                        (Speed >= Speed_R && (Speed <= Speed + Brake_Trigger_Emergency)) ? HighBrake : EmergencyBrake;

                StartFlags.StartCarManagement = 1;
            }

            if( Current_Velocity > -1.0 && Current_Velocity <= 1.0 ) // стоим на месте или едем очень медленно
            {
                /*!
                *   @note Здесь мы едем медленно или стоим и пришлои сообщение об уменьшении скорости
                */
                Transmission = (Speed >= -1.0 && Speed <= 1.0) ? N :
                               (Speed < -1.0) ? R : N;

                Brake = (Speed < -1.0) ? FullOut :
                        (Speed >= -1.0 && Speed <= 1.0) ? HighBrake : EmergencyBrake;
            }

            if( Current_Velocity > 1.0 && Current_Velocity <= 3.333 ) // скорость в диапазоне первой передачи
            {
                /*!
                *   @note Уменьшение скорости когда машина едет прямо на первой передаче
                */
                if( Transmission_Flag != F1) Transmission = F1;

                if( Speed <= 1.5) Transmission = N;

                Brake = (Speed >= Speed_R && (Brake_Trigger_Low >= Speed - Divider)) ? FullOut :
                        (Speed >= Speed_R && (Brake_Trigger_Medium >= Speed - Divider)) ? LowBrake :
                        (Speed >= Speed_R && (Brake_Trigger_High >= Speed - Divider)) ? MiddleBrake :
                        (Speed >= Speed_R && (Brake_Trigger_Emergency >= Speed - Divider)) ? HighBrake : EmergencyBrake;
            }

//            if( Current_Velocity > 3.333 && Current_Velocity <= 5.0) // скорость в диапазоне второй передачи
//            {
//                /*!
//                *   @note Уменьшение скорости когда машина едет прямо на второй передаче
//                */
//
//                if( Transmission != F2) Transmission = F2;
//
//                if( Speed <= 2.778 ) Transmission = F1;
//
//                Brake = ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Low) ) ? FullOut :
//                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Medium) ) ? LowBrake :
//                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_High) ) ? MiddleBrake :
//                        ((Speed <= 5.0) && (Speed >= Speed - Brake_Trigger_Emergency) ) ? HighBrake : EmergencyBrake;
//            }
        }

        if( Divider > Vel_Divider) // увеличение скорости
        {

            if( Current_Velocity < -1.0 && Current_Velocity > -3.333) // едем в диапазоне реверсивной передачи
            {
                /*!
                *   @note Пришло сообщение о увеличении скорости, то есть уменьшенить скорость в движении назад
                */
                Transmission = (Speed >= -3.333 && Speed < -1.0) ? R :
                               (Speed >= -1.0 && Speed <= 1.0) ? N : N;

                Brake = (Speed >= Speed_R && (Brake_Trigger_Low >= Speed - Divider)) ? FullOut :
                        (Speed >= Speed_R && (Brake_Trigger_Medium >= Speed - Divider)) ? LowBrake :
                        (Speed >= Speed_R && (Brake_Trigger_High >= Speed - Divider)) ? MiddleBrake :
                        (Speed >= Speed_R && (Brake_Trigger_Emergency >= Speed - Divider)) ? HighBrake : EmergencyBrake;
            }

            if( Current_Velocity >= -1.0 && Current_Velocity <= 1.0 ) // стоим на месте или едем очень медленно
            {
                /*!
                *   @note Пришло сообщение о ускорении, мы стоим
                */
                Transmission = (Speed >= -1.0 && Speed <= 1.0) ? N :
                               (Speed > 1.0) ? F1 : N;

                Brake = FullOut;
            }

            if( Current_Velocity > 1.0 && Current_Velocity <= 3.333 ) // скорость в диапазоне первой передачи
            {
                /*!
                *   @note Пришло сообщение о увеличении скорости когда мы едем на первой передаче
                */
                Transmission = ( Speed > 1.0 && Speed <= 4.16667) ? F1 :
                               ( Speed > 4.16667 && Speed <= 5.55) ? F2 : F1;

                Brake = FullOut;
            }

//            if( Current_Velocity > 3.333 && Current_Velocity <= 5.0) // скорость в диапазоне второй передачи
//            {
//                /*!
//                *   @note Опасный участок. Едем на второй и просят ускориться
//                */
//                Transmission = F2;
//
//                Brake = FullOut;
//
//            }
        }

        xStatus = pdFALSE;
        if( Brake != NONE) // назначение команд тормозу
        {
                if( (Brake == MiddleBrake || Brake == HighBrake || Brake == EmergencyBrake) )
                {
                    if( Clutch_Flag != Full)
                    {
                        Clutch = 0;
                        xStatus = xQueueSend(xQueueClutchHandle, &Clutch, portMAX_DELAY);
                    }
                }
                xStatus = xQueueSend(xQueueBrakeHandle, &Brake, portMAX_DELAY);
            xEvent = xEventGroupWaitBits(xEventStatus, Brake_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
        }

        if( Transmission != Transmission_Flag && Transmission_Flag != 15) // команды коробке передач
        {
            // если не было нажато сцепление - нажать
             if( Clutch_Flag != Full) { Clutch = 0; xStatus = xQueueSend(xQueueClutchHandle, &Clutch, portMAX_DELAY); }
             xStatus = xQueueSend(xQueueTransmissionHandle, &Transmission, portMAX_DELAY);


             xEvent = xEventGroupWaitBits(xEventStatus, ( Transmission_BIT | Clutch_BIT), pdTRUE, pdTRUE, portMAX_DELAY);

                Clutch = Full;
                xStatus = xQueueSend(xQueueClutchHandle, &Clutch, portMAX_DELAY);
        }
        xEvent = xEventGroupClearBits(xEventStatus, ALL_BITS);

    }
vTaskDelete(NULL);
}

// xTrInit
void vTransmissionInit( void *pvParameters)
{
    /*!
    *   @note Ручное управление коробкой передач
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
