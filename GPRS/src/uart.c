/*
 * uart.c
 *
 *  Created on: 21 jun. 2017
 *      Author: Propietario
 */

#include "uart.h"
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

/**
  * @brief  Configuracion de la UART
  * @param  None
  * @retval None
  */
void UART_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIOA_CLK_ENABLE();
//	GPIOB_CLK_ENABLE();
//
//    __USART1_CLK_ENABLE();
//
//    /**USART1 GPIO Configuration
//    PB6     ------> USART1_TX
//    PB7     ------> USART1_RX
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//    /* Peripheral DMA init*/
//
//    hdma_usart1_tx.Instance = DMA1_Channel2;
//    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
//    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    hdma_usart1_tx.Init.Mode = DMA_CIRCULAR;
//    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
//    HAL_DMA_Init(&hdma_usart1_tx);
//
//    __HAL_LINKDMA(&huart1,hdmatx,hdma_usart1_tx);
//
//    hdma_usart1_rx.Instance = DMA1_Channel3;
//    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
//    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
//    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
//    HAL_DMA_Init(&hdma_usart1_rx);
//
//    __HAL_LINKDMA(&huart1,hdmarx,hdma_usart1_rx);
//
//    __DMA1_CLK_ENABLE();
//
//    /* DMA interrupt init */
//    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

    /* Peripheral clock enable */
    __USART2_CLK_ENABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART6_TX
    PA3     ------> USART6_RX
    */
    GPIO_InitStruct.Pin 	  	= GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode   		= GPIO_MODE_AF_PP; //GPIO_MODE_ANALOG?
    GPIO_InitStruct.Pull   		= GPIO_NOPULL;
    GPIO_InitStruct.Speed 	  	= GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate 	= GPIO_AF1_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  Inicializacion de la UART
  * @param  None
  * @retval None
  */
void UART1_Init(void) {
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart1);

}

/**
 * @brief  Inicializacion de la UART
 * @param  None
 * @retval None
 */
void UART2_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);

	HAL_NVIC_SetPriority(USART2_IRQn, 0x1, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle: UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
 {
	HAL_NVIC_SetPendingIRQ(USART2_IRQn);
}


/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	HAL_NVIC_SetPendingIRQ(USART2_IRQn);
}

void imprimir(char* msg) {
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), 0xFFFF);
}

