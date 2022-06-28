#include "main.h"
#define Test      1     // ���� ����� ��������� ������������ ��������� ������ �� �������

int main(void)
{
    BoardStart();
    PID_Init();
#if (Test == 0)

    // ���������� �������� � �������
    vSemaphoreCreateBinary(xStartEvent);
    xTaskCreate(vRobotGo, (char *) "SET/RESET", configMINIMAL_STACK_SIZE, NULL, 3, &xRobotGo);
    vTaskSuspend(xRobotGo);

    // ����� �������
    xTaskCreate(vStart, (char *) "START", configMINIMAL_STACK_SIZE, NULL, 2, &xStartHandle);

    // �������� ��������� � UART
    vSemaphoreCreateBinary(xUARTEvent);
    xTaskCreate(vWaitingEvent, (char *) "Events", configMINIMAL_STACK_SIZE, NULL, 1, &xWaitingHandle);
    vTaskSuspend(xWaitingHandle);

    // ������������� �������� ���������
    xTaskCreate(vMessageSending, (char *) "Mail", configMINIMAL_STACK_SIZE, NULL, 1, &xMailHandle);
    vTaskSuspend(xMailHandle);

    // ���������� ����������
    xTaskCreate(vClutchManagement, (char *) "Clutch", configMINIMAL_STACK_SIZE, NULL, 1, &xClutchHandle);
    vTaskSuspend(xClutchHandle);

    // ���������� ��������
    xTaskCreate(vBrakeManagement, (char *) "Brake", configMINIMAL_STACK_SIZE, NULL, 1, &xBrakeHandle);
    vTaskSuspend(xBrakeHandle);

    // ���������� �����
    xTaskCreate(vGasManagement, (char *) "Gas", configMINIMAL_STACK_SIZE, NULL, 1, &xGasHandle);
    vTaskSuspend(xGasHandle);

    // ���������� ������������
    xTaskCreate(vManagementGearsBox, (char *) "Gear", configMINIMAL_STACK_SIZE, NULL, 1, &xGearsHandle );
    vTaskSuspend(xGearsHandle);

    // ������������ � �������� ������� �� ModBus
    xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );
    vTaskSuspend(xModBusHandle);

    // �������� ��������� ������� � ����������� �������� ������ �������
    xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 1, &xQueueManagHandle );
    vTaskSuspend(xQueueManagHandle);

    // ������ ������������� �������� �������
    xTaskCreate(vTransmissionInit,(char *) "INIT", configMINIMAL_STACK_SIZE, NULL, 1, &xTrInit);
    vTaskSuspend(xTrInit);

    xQueue20Handle = xQueueCreate(3, sizeof(float)); /// Queue storing new velocity
    xQueueBrakeHandle = xQueueCreate(3, sizeof(uint8_t)); /// Queue Brake Value
    xQueueTransmissionHandle = xQueueCreate(1, sizeof(uint8_t)); /// Queue Transmission Value
    xQueueClutchHandle = xQueueCreate(3, sizeof(uint8_t)); /// Queue Clutch Value

    if( xQueue20Handle != NULL &&
        xQueueBrakeHandle != NULL &&
        xQueueTransmissionHandle != NULL &&
        xQueueClutchHandle != NULL) { vTaskStartScheduler(); }
#elif (Test == 1)
    /* here not enter when RTOS is on or test not select */
    while(1)
    {
        move_transmission_to_certain_state();
        /*!
        *   @note Main: < ��� ����� ������� ������� >
        */
    }
#endif
}
