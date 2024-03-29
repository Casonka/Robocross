
#include "ModBus.h"

/*
    Info for Modbus
    20 - ��������� ������� ������� � �������� ����������
    21 - ������
    22 - ?

*/
static unsigned int Error;
#define UART_SIMULATION     0

/*!
*   @brief ModBus_Init - function for initialize ModBus protocol
*       @arg - NONE
*/

// To send the velocity

unsigned char StartFrameSend[15] = {':', 'D', '0', '0', '6', '+', '0', '0', '0', '0', '0', 'A', 'A', '\r', '\n'};
unsigned char *StartDataSendIndex;
unsigned char *LRCPointer;
void ModBus_Init(void) {

    Error = 0;
    UARTBufferStartMsgPointer = UART_Buffer;
    UARTBufferEndMsgPointer = UART_Buffer + ( UART_BUFFER_SIZE - 1 );
    UARTBufferLRCIndex = UARTBufferEndMsgPointer - 3;
    UARTReceiver_Flag = 0;
    ModBus_ClearMsgs();

    StartDataSendIndex = StartFrameSend + 6;
    LRCPointer = StartFrameSend + 11;

    Queue_StartIndex = QueueBuffer_To_UART;
    Queue_EndIndex = Queue_StartIndex + ( QueueSize - 1 );
    Queue_Index = Queue_StartIndex;

    #if (UART_SIMULATION == 1)
    unsigned char Data[UART_BUFFER_SIZE] = {':', 'D', '2', '0', '6', '2', '0', '+', '5', '5', '5', 'B', 'E', '\r', '\n' }; // 15 size
    for(int i = 0; i < UART_BUFFER_SIZE; i++)
    {
        UART_Buffer[i] = Data[i];
        UARTBufferIndex++;
    }
    unsigned int Dat;
    Error = ModBus_CheckFrame();
    (Error == 0) ? Dat = ModBus_ParsePacket() : ModBus_ClearMsgs();
    ModBus_ClearMsgs();
    ModBus_SendResponse(":D00600+555C2\r\n");
    #endif
}

void ModBus_QueueClear(void)
{
    Queue_StartIndex = QueueBuffer_To_UART;
    Queue_EndIndex = Queue_StartIndex + ( QueueSize - 1 );
    Queue_Index = Queue_StartIndex;
    for(int i = 0; i <= (QueueSize - 1); i++) {QueueBuffer_To_UART[i] = 0;}
}

/*!
*   @brief LRC_Counting - function for calculating LRC
*       @arg - NONE
*/

unsigned char LRC_Counting(unsigned char *buf, unsigned short bsize) {
    unsigned char * pData = buf;
    unsigned char LRC = 0;
    while(bsize--)
    {
        LRC += *pData++;
    }
    return ((unsigned char)(-((char)LRC)));
}

void ModBus_DEC_TO_ASCII_Converter(unsigned int *DEC_Pointer, unsigned short bsize)
{
    unsigned char ASCII;
    ASCII = 0;
    for(int i = 0; i <= bsize; i++)
    {
        ASCII = *DEC_Pointer++;
        ASCII += 0x30;
        *StartDataSendIndex++ = ASCII;
    }
    StartDataSendIndex = StartFrameSend + 6;
}

void ModBus_HEX_TO_ASCII_Converter(unsigned int *HEX_Pointer, unsigned short bsize)
{
    unsigned char ASCII;
    ASCII = 0;
    for(int i = 0; i <= bsize; i++)
    {
        ASCII = *HEX_Pointer++;
        if( ASCII > 0x9) { ASCII -= 0xA; ASCII += 0x41;}
        if( ASCII >= 0x00 && ASCII <= 0x9) { ASCII += 0x30;}
        *LRCPointer = ASCII;
        LRCPointer++;
    }
    LRCPointer = StartFrameSend + 11;
}

unsigned int ModBus_ASCII_TO_HEX_Converter(unsigned char *ASCII_Pointer, unsigned short bsize)
{
    unsigned int HEX, i, Result;
    Result = 0; HEX = 0; i = 0;
    for(i = 0; i <= bsize; i++)
    {
        HEX = ((unsigned int)*(ASCII_Pointer + i));
        if (((unsigned int)(HEX)) > '9') { HEX = (unsigned int)(HEX&0xF) + 9; }
        else { HEX &= 0xF;}
        Result |= (unsigned int) (HEX << (4 * (bsize - i)));
    }
    return Result;
}

/*!
*   @brief ModBus_ClearMsgs - function for clear current UART buffer
*       @arg - NONE
*/

void ModBus_ClearMsgs(void) {

for(int i = 0; i < UART_BUFFER_SIZE;i++)
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
            const unsigned char EndFrame[2] = { 13, 10 };
            unsigned char Tmp[2];
            int counts = 0;
            for (int i = 0; i <= 1; i++)
            {
                Tmp[i] = *(UARTBufferEndMsgPointer - (1 - i));
                if (Tmp[i] == EndFrame[i]) {counts++;}
            }
           if(counts == 2) {return 0x00;} else {return 0x08;}
        }
    return 0x08;
}

float ModBus_ParsePacket(void) {
    static unsigned char *UARTBufferSlaveAddrIndex;
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
    if(UARTReceiver_Flag == 0) {return 0;}

    unsigned char TmpLRC = LRC_Counting(UARTBufferStartMsgPointer,
            (unsigned short)(( UARTBufferEndMsgPointer - 4 ) - UARTBufferStartMsgPointer) + 1);
    unsigned char LRCMsgs = ModBus_ASCII_TO_HEX_Converter(UARTBufferLRCIndex,
                                                         ((unsigned short)((UARTBufferLRCIndex + 1) - UARTBufferLRCIndex)));

    if( TmpLRC == LRCMsgs)
    {
        unsigned char *UARTBufferFunstionMsgPointer;
        UARTBufferFunstionMsgPointer = UARTBufferStartMsgPointer + 3;
        unsigned int MessageMode;

        MessageMode = ModBus_ASCII_TO_HEX_Converter(UARTBufferFunstionMsgPointer,
                                                   ((unsigned short)((UARTBufferFunstionMsgPointer + 1) - UARTBufferFunstionMsgPointer)));

        switch (MessageMode)
        {

            case 0x06:  //writing new value
            {
                unsigned char *UARTBufferDataMsgPointer;
                UARTBufferDataMsgPointer = UARTBufferStartMsgPointer + 5;
                unsigned int ManageSector = ModBus_ASCII_TO_HEX_Converter(UARTBufferDataMsgPointer,
                                                                         ((unsigned short)((UARTBufferDataMsgPointer + 1) - UARTBufferDataMsgPointer)));
                if(ManageSector == 0x20)    // velocity
                {
                    unsigned char UARTBufferDirMsg = *(UARTBufferStartMsgPointer + 7);
                    UARTBufferDataMsgPointer = UARTBufferStartMsgPointer + 8;

                    unsigned int Data_hex = ModBus_ASCII_TO_HEX_Converter(UARTBufferDataMsgPointer,
                                                                     ((unsigned short)((UARTBufferDataMsgPointer + 2) - UARTBufferDataMsgPointer)));
                    if( Data_hex > 0x500) { Data_hex = 0x500; }
                    Data_hex = ((unsigned int)(((unsigned int)(Data_hex * 3331)) >> 13));
                    float Data_Dec = ((float)Data_hex) / 100;
                    if (UARTBufferDirMsg == '-') {Data_Dec = -Data_Dec;}
                    UARTReceiver_Flag = 0;
                    return Data_Dec;
                }
            }
        }
    }
UARTTransmit_Flag = 0;
UARTReceiver_Flag = 0;
return 0;
}

unsigned int ModBus_IsFull_Queue(void)
{
    switch (UARTTransmit_Flag)
    {
        case 1: // answer :OK - SUCCESS
        {
            if( Queue_Index > (Queue_StartIndex + 4) ) { return 1; }
            else { return 0; }
            break;
        }

        case 2 : // answer: ERR - ERROR
        {
            if( Queue_Index > Queue_StartIndex + 5 ) { return 1; }
            else { return 0; }
            break;
        }

        case 3: // answer: value - ANGLE
        {
            if( Queue_Index > Queue_EndIndex ) { return 1; }
            else { return 0; }
            break;
        }

        default :
        {
            return 0;
            break;
        }
    }
}

void ModBus_SendResponse(unsigned  char* Resp)
{
    while(*Resp != '\0') { ModBus_SendByte(*Resp); Resp++; }
}

void ModBus_PutQueue(const volatile char Data)
{
    if( ModBus_IsFull_Queue() == 1 )
    {
        Queue_Index = Queue_StartIndex;
        int i;
        for(i = 0; i <= 3; i++ ) { QueueBuffer_To_UART[i] = 0;}
    }
    *Queue_Index++ = Data;
}

void ModBus_SendResponseSpeed(float Speed)
{
    unsigned int DataBuf[5] = {0, 0, 0, 0, 0};

    if(Speed < 0) {*(StartDataSendIndex - 1) = '-'; Speed = -Speed;}
    else {*(StartDataSendIndex - 1) = '+';}

    DataBuf[0] = Speed/10000;
    DataBuf[1] = Speed/1000 - ((unsigned int)(Speed/10000))*10;
    DataBuf[2] = Speed/100 - ((unsigned int)(Speed/1000))*10;
    DataBuf[3] = Speed/10  - ((unsigned int)(Speed/100))*10;
    DataBuf[4] = Speed - ((unsigned int)(Speed/10))*10;

    ModBus_DEC_TO_ASCII_Converter(DataBuf, (unsigned short)((*DataBuf + 4) - (*DataBuf)));

    unsigned char Tmp  = LRC_Counting(StartFrameSend,
            ((unsigned short)(( StartDataSendIndex + 5) - StartFrameSend)));
    unsigned int Buf[2];
    Buf[0] = Tmp >> 4;
    Buf[1] = Tmp&0xF;
    ModBus_HEX_TO_ASCII_Converter(Buf, ((unsigned short)((LRCPointer + 1) - LRCPointer)));
    ModBus_SendResponse(StartFrameSend);
}

unsigned char *QueueIndexTx;

unsigned int Get_Queue(void) { return *QueueIndexTx++; }

void ModBus_SendByte(const char Data)
{
    while (!USARTGetStatus(usart3,TransmitRegEmpty)) {}
    ModBus_PutQueue(Data);
    if ( ModBus_IsFull_Queue() == 1)
    {
        QueueIndexTx = Queue_StartIndex;
        while(*QueueIndexTx != '\0')
            {
            if((USART3->SR & 0x80) >> 7)
            {
                    volatile uint8_t Da = ((uint8_t)Get_Queue());
                    USART3->DR = (unsigned int)Da;
            }
            }
        UARTTransmit_Flag = 0;
        ModBus_QueueClear();
    }
}


