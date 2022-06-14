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
    USARTBothConfigure(usart3, 121 , 0, 1);     // 14 МГц ??
    // 2500 - буквы не показывает (примерно 4800 бод)
    // 2916 - все ок ( почти 4800 бод )
    // 2187 - все плохо
    // 1458 - вроде ок ( около 9600 бод)
    // 1250 - все плохо
    // 857 - все хорошо ( около 14400 бод )
    // 729 - все хорошо ( около 19200 бод)
    // 121 - все хорошо (около 115200 бод)
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
