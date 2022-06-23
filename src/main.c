#include "main.h"
#define Test        0   // ���� ����� ��������� ������������ ��������� ������ �� ������� 1
int Transmission;
_Bool flag = 1;
int main(void)
{
    BoardStart();
    PID_Init();
    Transmission = 0;
#if (Test == 0)
    // ����� �������
    xTaskCreate(vStart, (char *) "START", configMINIMAL_STACK_SIZE, NULL, 2, &xStartHandle);

    // ���������� ����������
    xTaskCreate(vClutchManagement, (char *) "CLUTCH", configMINIMAL_STACK_SIZE, NULL, 1, &xClutchHandle);

    // ���������� ��������
    xTaskCreate(vBrakeManagement, (char *) "BRAKE", configMINIMAL_STACK_SIZE, NULL, 1, &xBrakeHandle);

    xTaskCreate(vGasManagement, (char *) "GAS", configMINIMAL_STACK_SIZE, NULL, 1, &xGasHandle);

    // �������� ��������� �� ModBus � �������� �������
    xTaskCreate(vWaitingEvent, (char * )"Wait", configMINIMAL_STACK_SIZE, NULL,1, &xWaitingHangle );

    // ���������� ������������
    xTaskCreate(vManagementGearsBox, (char *) "GEAR", configMINIMAL_STACK_SIZE, NULL, 1, &xGearsHandle );

    // ������������ � �������� ������� �� ModBus
    xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );

    // �������� ��������� ������� � ����������� �������� ������ �������
    xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 1, &xQueueManagHandle );

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
        *   @note Main: < ��� ����� ������� ������� >
        */

    }
#endif
}
