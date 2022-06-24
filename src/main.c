#include "main.h"
#define Test        0   // если нужно запустить тестирование отдельных блоков то ставьте 1


int main(void)
{
    BoardStart();

#if (Test == 0)

    // разрешение движения и рестарт
    vSemaphoreCreateBinary(xStartEvent);
    xTaskCreate(vRobotGo, (char *) "SET/RESET", configMINIMAL_STACK_SIZE, NULL, 3, &xRobotGo);
    vTaskSuspend(xRobotGo);

    // Старт системы
    xTaskCreate(vStart, (char *) "START", configMINIMAL_STACK_SIZE, NULL, 2, &xStartHandle);

    xTaskCreate(vWaitingEvent, (char *) "Events", configMINIMAL_STACK_SIZE, NULL, 1, &xWaitingHandle);
    vTaskSuspend(xWaitingHandle);

    // периодическая отправка сообщений
    xTaskCreate(vMessageSending, (char *) "Mail", configMINIMAL_STACK_SIZE, NULL, 1, &xMailHandle);
    vTaskSuspend(xMailHandle);

    // Управление сцеплением
    xTaskCreate(vClutchManagement, (char *) "Clutch", configMINIMAL_STACK_SIZE, NULL, 1, &xClutchHandle);
    vTaskSuspend(xClutchHandle);

    // Управление Тормозом
    xTaskCreate(vBrakeManagement, (char *) "Brake", configMINIMAL_STACK_SIZE, NULL, 1, &xBrakeHandle);
    vTaskSuspend(xBrakeHandle);

    // Управление газом
    xTaskCreate(vGasManagement, (char *) "Gas", configMINIMAL_STACK_SIZE, NULL, 1, &xGasHandle);
    vTaskSuspend(xGasHandle);

    // Управление трансмиссией
    xTaskCreate(vManagementGearsBox, (char *) "Gear", configMINIMAL_STACK_SIZE, NULL, 1, &xGearsHandle );
    vTaskSuspend(xGearsHandle);

    // Формирование и передача пакетов по ModBus
    vSemaphoreCreateBinary(xUARTEvent);
    xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );
    vTaskSuspend(xModBusHandle);

    // Проверка элементов очереди и направление значений другим задачам
    xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 1, &xQueueManagHandle );
    vTaskSuspend(xQueueManagHandle);

    xQueue20Handle = xQueueCreate(3, sizeof(float)); /// Queue storing new velocity
    xQueueBrakeHandle = xQueueCreate(3, sizeof(uint8_t)); /// Queue Brake Value
    xQueueTransmissionHandle = xQueueCreate(3, sizeof(uint8_t)); /// Queue Transmission Value

    if( xQueue20Handle != NULL &&
        xQueueBrakeHandle != NULL &&
        xQueueTransmissionHandle != NULL) { vTaskStartScheduler(); }
#elif (Test == 1)
    /* here not enter when RTOS is on and Queue create successful or test not select */
    while(1)
    {
        /*!
        *   @note Main: < для теста функции вручную >
        */
        MoveTo(direction, TransmissionPWM);
    }
#endif
}
