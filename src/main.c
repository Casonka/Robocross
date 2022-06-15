#include "main.h"

int main(void)
{

    BoardStart();
    xTaskCreate(vInitMainSectors, (char *) "STM", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
    xTaskCreate(vWaitingEvent, (char * )"Wait", configMINIMAL_STACK_SIZE, NULL,2, &xWaitingHangle );
    xTaskCreate(vManagementGearsBox, (char *) "GEAR", configMINIMAL_STACK_SIZE, NULL, 1, &xGearsHandle );
    xTaskCreate(vClutchManagement, (char *) "Clutch", configMINIMAL_STACK_SIZE, NULL, 1, &xClutchHandle);
    xTaskCreate(vModBusManagement, (char *) "ModBus", configMINIMAL_STACK_SIZE, NULL, 1, &xModBusHandle );
    xTaskCreate(vSecurityMemoryManagement, (char *) "Queue", configMINIMAL_STACK_SIZE, NULL, 1, &xQueueManagHandle );

    set_pin(PIN4_12V); set_pin(PIN5_12V); set_pin(PIN6_12V);
    xQueue20Handle = xQueueCreate(3, sizeof(unsigned int)); /// Queue storing new velocity

    if( xQueue20Handle != NULL ) { vTaskStartScheduler(); }
    /* here not enter when RTOS is on and Queue create successful */
    while(1)    {}
}
