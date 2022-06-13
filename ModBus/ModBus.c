
#include "ModBus.h"

/*
    Info for Modbus
    200 - положение коробки передач
    201 - скорость машины
    202 - ?

*/
static unsigned int Error;
#define UART_SIMULATION     1

/*!
*   @brief ModBus_Init - function for initialize ModBus protocol
*       @arg - NONE
*/

void ModBus_Init(void) {

    Error = 0;
    UARTBufferStartMsgPointer = UART_Buffer;
    UARTBufferEndMsgPointer = UART_Buffer + ( UART_BUFFER_SIZE - 1 );
    UARTBufferLRCIndex = UARTBufferEndMsgPointer - 5;
    UARTReceiver_Flag = 0;
    ModBus_ClearMsgs();

    #if (UART_SIMULATION == 1)
    unsigned char Data[UART_BUFFER_SIZE] = {':', 'D', '2', '0', '6', '2', '0', '0', '+', '1', 'F', 'C', '0', '\r', '0', '\n' };
    for(int i = 0; i < UART_BUFFER_SIZE; i++)
    {
        UART_Buffer[i] = Data[i];
        UARTBufferIndex++;
    }
    Error = ModBus_CheckFrame();
    (Error == 0) ? ModBus_ParsePacket() : ModBus_ClearMsgs();
    #endif
}

static unsigned char LRC_Counting(unsigned char *buf, unsigned short bsize) {
    unsigned char * pData = buf;
    unsigned char LRC = 0;
    while(bsize--)
    {
        LRC += *pData++;
    }
    return ((unsigned char)(-((char)LRC)));
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
*   @brief ModBus_CheckFrame - function for check input buffer
*       @arg - NONE
*/

unsigned int ModBus_CheckFrame(void) {

    if( *UARTBufferStartMsgPointer == ':')
        {
            const unsigned char EndFrame[4] = {'0', '\r', '0', '\n'};
            unsigned char Tmp[4];
            int counts = 0;
            for (int i = 0; i <= 3; i++)
            {
                Tmp[i] = *(UARTBufferEndMsgPointer - (3 - i));
                if (Tmp[i] == EndFrame[i]) {counts++;}
            }
           if(counts == 4) {return 0;} else {return 1;}
        }
    return 1;
}

void ModBus_ParsePacket(void) {

    const unsigned char Slave_Address[2] = {'D', '2'};

    unsigned char Tmp[2];
    UARTBufferSlaveAddrIndex = UARTBufferStartMsgPointer + 1;
    int counts = 0;
    for(int i = 0; i <= 1; i++)
    {
        Tmp[i] = *(UARTBufferSlaveAddrIndex + i);
        if(Tmp[i] == Slave_Address[i]) {counts++;}
    }
    if(counts == 2) { UARTReceiver_Flag = 1; }
    if(UARTReceiver_Flag == 0) {return;}

    unsigned char TmpLRC = LRC_Counting(UARTBufferStartMsgPointer,
            (unsigned short)(( UARTBufferEndMsgPointer - 6 ) - UARTBufferStartMsgPointer) + 1);



}


