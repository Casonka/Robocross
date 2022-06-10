#include "main.h"

#define RTOS_Mode   0


int main(void)
{


    #if( RTOS_MODE == 0 ) // all
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 1 ) // GearBox Car
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 2 ) // Encoders Car
    xTaskCreate(vManagementGearsBox, (char *) "car", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    #elif ( RTOS_MODE == 3 ) // UART connection

    #else
    #error Invaid value of RTOS_MODE
    #endif
    vTaskStartScheduler();
    // here not enter while Scheduler is on
    while(1)    {}
}
