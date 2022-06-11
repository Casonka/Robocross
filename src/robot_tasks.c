#include "robot_tasks.h"

// System functions
//--------------------------------------------------------------------------------------------------------------------
void vApplicationTickHook(void){
/*!
*   @brief vApplicationIdleHook(void) - функция бездействия, выполняется когда процессорное время ничем не занято
*   @argument nothing - функция ничего не получает и ничего не возвращает
*
*/
}

void vApplicationIdleHook(void)
{

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{

}

void vApplicationMallocFailedHook( void )
{

}

// Tasks functions
//----------------------------------------------------------------------------------------------------------------------
void vManagementGearsBox( void *pvParameters )  //car management gears box ( enter code here man!)
{
for(;;) {

}
vTaskDelete(NULL);
}

void vUartManagement( void *pvParameters )
{
    for(;;)
    {


    }
vTaskDelete(NULL);
}

//-------------------------------------------------------------------------------------------------------------------------
