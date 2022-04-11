#include "main.h"


int main(void)
{

    xBuffer = xQueueCreate(5,sizeof(int));
    if(xBuffer != NULL)
    {
    //xTaskCreate(vTask1,"Task1",configMINIMAL_STACK_SIZE,NULL,1,NULL);
    vTaskStartScheduler();
    }

    while(1)
    {

    }
}
