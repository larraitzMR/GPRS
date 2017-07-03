/*
 * gprs.c
 *
 *  Created on: 26 jun. 2017
 *      Author: Propietario
 */

#include "main.h"
#include "gprs.h"
#include "uart.h"
#include "i2c.h"
#include <string.h>

extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;


/**
  * @brief  Send an AT command string
  * @param  String command
  * @param  Timeout in ms
  * @retval None
  */
void send_ATCommand(char *cmd, uint32_t esp_timeout)
{
  uint16_t cmd_len = strlen(cmd);

  if (HAL_UART_Transmit(&huart1, (uint8_t *)cmd, cmd_len, esp_timeout) != HAL_OK) {
	  imprimir("Error");
  }
}

void send_ATCommand_DMA(char *cmd)
{
  uint16_t cmd_len = strlen(cmd);

  if (HAL_UART_Transmit_DMA(&huart1, (uint8_t *)cmd, cmd_len) != HAL_OK) {
	  imprimir("Error");
  }
}

void write_command(char *cmd, uint32_t esp_timeout)
{
	while (HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) I2C_ADDRESS ,(uint8_t*)cmd, 4, 1000) != HAL_OK) {
		if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
			imprimir("Error");
		}
	}

	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {
	}
}

uint8_t RXBUFFERSIZE = 2;
uint8_t aRxBuffer[5];

void read_buffer()
{
	while (HAL_I2C_Master_Receive(&hi2c1, (uint16_t) I2C_ADDRESS, (uint8_t *) aRxBuffer, RXBUFFERSIZE, 1000) != HAL_OK) {
		if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
			imprimir("Error");
		}
	}
	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {
	}
	 imprimir(aRxBuffer);
}
