/*
 * uart.h
 *
 *  Created on: 21 jun. 2017
 *      Author: Propietario
 */

#define GPIOA_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define GPIOA_CLK_DISABLE()				__HAL_RCC_GPIOA_CLK_DISABLE()

#define GPIOB_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define GPIOB_CLK_DISABLE()				__HAL_RCC_GPIOB_CLK_DISABLE()

#define USART2_CLK_ENABLE()				__USART2_CLK_ENABLE();

void UART_Config(void);
void UART1_Init(void);
void UART2_Init(void);

void imprimir(char* msg);

