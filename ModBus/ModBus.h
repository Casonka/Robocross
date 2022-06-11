#pragma once

#define UART_BUFFER_SIZE    16

unsigned char UART_Buffer[UART_BUFFER_SIZE];
unsigned char *UARTBufferIndex;
unsigned char *UARTBufferStartMsgPointer;
unsigned char *UARTBufferEndMsgPointer;

void ModBus_Init(void);

void ModBus_ClearMsgs(void);    /// Clear UART Buffer

unsigned int ModBus_CheckFrame(void);   /// Check buffer for 0x3A.../r/n

void ModBus_ParsePacket(void);  /// Check and get answer, write new value
