#pragma once

#define UART_BUFFER_SIZE    16

unsigned char UART_Buffer[UART_BUFFER_SIZE];
static unsigned char *UARTBufferIndex;
static unsigned char *UARTBufferStartMsgPointer;
static unsigned char *UARTBufferSlaveAddrIndex;
static unsigned char *UARTBufferLRCIndex;
static unsigned char *UARTBufferEndMsgPointer;

static unsigned int UARTReceiver_Flag;

void ModBus_Init(void);

static unsigned char LRC_Counting(unsigned char *buf, unsigned short bsize);

void ModBus_ClearMsgs(void);    /// Clear UART Buffer

unsigned int ModBus_CheckFrame(void);   /// Check buffer for 0x3A.../r/n

void ModBus_ParsePacket(void);  /// Check and get answer, write new value
