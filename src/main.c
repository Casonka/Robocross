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
    #if( RTOS_MODE == 0 ) // None
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 1 ) // GearBox Car
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 2 ) // Encoders Car
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 3 ) // UART connection
    xTaskCreate(vUartManagement, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    #else
    #error Invaid value of RTOS_MODE
    #endif
    vTaskStartScheduler();
    /* here not enter when RTOS is on */
    while(1)    {}
}
