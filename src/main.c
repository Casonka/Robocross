#include "main.h"

struct {

uint32_t Systick;
uint32_t AHB;
uint32_t APB1;
uint32_t APB2;

} Clocks;

int main(void)
{

    BoardStart;
    xTaskCreate(vInitMainSectors, (char *) "STM", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
    xTaskCreate(vManagementGearsBox, (char *) "GEAR", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
    xTaskCreate(vModBusManagement, (char *) "UART", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    vTaskStartScheduler();
    /* here not enter when RTOS is on */
    while(1)    {}
}
