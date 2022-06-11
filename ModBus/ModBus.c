
#include "ModBus.h"

/*
    Info for Modbus
    200 - положение коробки передач
    201 - скорость машины
    202 - ?

*/
unsigned int Error;
#define UART_SIMULATION     1

/*!
*   @brief ModBus_Init - function for initialize ModBus protocol
*       @arg - NONE
*/

void ModBus_Init(void) {
    Error = 0;
    UARTBufferStartMsgPointer = UART_Buffer;
    UARTBufferEndMsgPointer = UART_Buffer + ( UART_BUFFER_SIZE - 1 );
    ModBus_ClearMsgs();

    #if (UART_SIMULATION == 1)
    unsigned char Data[UART_BUFFER_SIZE] = {':', 'D', '2', '0', '6', '2', '0', '0', '0', '1', 'F', '7', '\r', '\n' };
    for(int i = 0; i < UART_BUFFER_SIZE; i++)
    {
        UART_Buffer[i] = Data[i];
        UARTBufferIndex++;
    }
    Error = ModBus_CheckFrame();
    #endif
}

/*!
*   @brief ModBus_ClearMsgs - function for clear current UART buffer
*       @arg - NONE
*/

void ModBus_ClearMsgs(void) {

for(int i = 0; i < sizeof(UART_Buffer);i++)
{
    UART_Buffer[i] = 0;

}
    UARTBufferIndex = UART_Buffer;
}

/*!
*   @brief ModBus_CheckFrame - function for initialize ModBus protocol
*       @arg - NONE
*/

unsigned int ModBus_CheckFrame(void) {

    if( *UARTBufferStartMsgPointer == ':')
        {
            const unsigned char EndFrame[2] = { '\r', '\n'};
            unsigned char Tmp[2] = ;


        }
    return 0;
}

void ModBus_ParsePacket(void) {
}


