#include "main.h"

struct {

uint32_t pllvco;
uint32_t Systick;
uint32_t AHB;
uint32_t APB1;
uint32_t APB2;

} Clocks;

int main(void)
{

    BoardStart;
    USARTBothConfigure(usart3, 121 , 0, 1);     // 14 ��� ??
    // 2500 - ����� �� ���������� (�������� 4800 ���)
    // 2916 - ��� �� ( ����� 4800 ��� )
    // 2187 - ��� �����
    // 1458 - ����� �� ( ����� 9600 ���)
    // 1250 - ��� �����
    // 857 - ��� ������ ( ����� 14400 ��� )
    // 729 - ��� ������ ( ����� 19200 ���)
    // 121 - ��� ������ (����� 115200 ���)
    xTaskCreate(vInitMainSectors, (char *) "STM", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
    xTaskCreate(vManagementGearsBox, (char *) "GEAR", configMINIMAL_STACK_SIZE, NULL, 2, &xGearsHandle );
    xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );
    xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskQueueManagHandle );

    xQueue20Handle = xQueueCreate(3, sizeof(unsigned int));
    //xQueue21Handle = xQueueCreate(3, sizeof(unsigned int));
    //xQueue22Handle = xQueueCreate(3, sizeof(unsigned int));
    if( xQueue20Handle != NULL ) { vTaskStartScheduler(); }
    /* here not enter when RTOS is on and Queue create successful */
    while(1)    {}
}
