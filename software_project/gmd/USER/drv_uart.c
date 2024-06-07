#include "drv_uart.h"

void uart0_init(uint32_t BaudRate)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = BaudRate;//Baud Rate

	UART_Init(UART0, &UART_InitStruct);
}
