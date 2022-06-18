#pragma once
#include <FilConfig.h>
#define UART_BUFFER_SIZE    15  //15

unsigned char UART_Buffer[UART_BUFFER_SIZE];
unsigned char *UARTBufferIndex;
unsigned char *UARTBufferStartMsgPointer;
unsigned char *UARTBufferLRCIndex;
unsigned char *UARTBufferEndMsgPointer;

#define QueueSize       15

unsigned char QueueBuffer_To_UART[QueueSize];
unsigned char *Queue_StartIndex;
unsigned char *Queue_EndIndex;
unsigned char *Queue_Index;

unsigned int UARTReceiver_Flag;
unsigned int UARTTransmit_Flag;

void ModBus_Init(void);

unsigned char LRC_Counting(unsigned char *buf, unsigned short bsize);

void ModBus_ClearMsgs(void);    /// Clear UART Buffer

unsigned int ModBus_CheckFrame(void);   /// Check buffer for 0x3A.../r/n

float ModBus_ParsePacket(void);  /// Check and get answer, write new value

void ModBus_SendResponse( unsigned char* Resp);

void ModBus_SendResponseSpeed(float Speed);

void ModBus_SendByte(const char Data);
