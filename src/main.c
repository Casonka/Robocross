#include "main.h"
#define Test     0     // ���� ����� ��������� ������������ ��������� ������ �� �������
_Bool once = 0;
int transmission = 0;
int main(void)
{
    BoardStart();
    PID_Init();
    //Get_Clutch();
#if (Test == 0)

    //xDeadTimeOut = xTimerCreate(xDeadTimeOut,)
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

    xQueue20Handle = xQueueCreate(1, sizeof(float)); /// Queue storing new velocity
    xQueueBrakeHandle = xQueueCreate(1, sizeof(uint8_t)); /// Queue Brake Command
    xQueueTransmissionHandle = xQueueCreate(1, sizeof(uint8_t)); /// Queue Transmission Command
    xQueueClutchHandle = xQueueCreate(1, sizeof(uint8_t)); /// Queue Clutch Command
    xQueueGasHandle = xQueueCreate(1, sizeof(uint8_t)); /// Queue Gas Command

    xEventStatus = xEventGroupCreate();

    if( xQueue20Handle != NULL &&
        xQueueBrakeHandle != NULL &&
        xQueueTransmissionHandle != NULL &&
        xQueueClutchHandle != NULL &&
        xQueueGasHandle != NULL) { vTaskStartScheduler(); }
#elif (Test == 1)
    /* here not enter when RTOS is on or test not select */
    //Clutch_Flag = 1;
    while(1)
    {
        if( once == 1)
        {

            //Move_Clutch(Full);
           //Set_Transmission(transmission);
            once = 0;
        }
        /*!
        *   @note Main: < ��� ����� ������� ������� >
        */
    }
#endif
}
