#include "main.h"

#define RTOS_Mode   3
struct {
uint32_t Systick;
uint32_t AHB;
uint32_t APB1;
uint32_t APB2;
} Clocks;

int main(void)
{

    BoardStart;

   // xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    xTaskCreate(vUartManagement, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    vTaskStartScheduler();
    /* here not enter when RTOS is on */
    while(1)    {}
}
