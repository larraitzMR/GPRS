/*
 * main.c
 *
 *  Created on: 21 jun. 2017
 *      Author: Larraitz
 */

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "uart.h"
#include "i2c.h"
#include "gprs.h"
#include <string.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

uint8_t buff[15];


/* Private functions ---------------------------------------------------------*/
char ctrlz = '\x1a';

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	HAL_Init();

	/* Configure the system clock to 48 MHz */
	SystemClock_Config();

	UART_Config();
//	UART1_Init();
	UART2_Init();

	I2C_Config();
	I2C1_Init();

	imprimir("Esto se imprime por TeraTerm!\r\n");


	while (1) {
//		send_ATCommand_DMA("AT\r\n");
//		HAL_UART_Receive_DMA(&huart1, (uint8_t *)buff, strlen(buff));
		write_command("AT\r\n", 1000);
		read_buffer();
		write_command("AT+CMGF=1\r\n", 1000);
		read_buffer();
		write_command("AT+CMGS=+34649103025\r\n", 1000);
		read_buffer();
		write_command("ieeeeeee\r\n", 1000);
		read_buffer();
		write_command("\x1A", 1000);
		read_buffer();


//		send_ATCommand("AT\r\n", 1000);
//		send_ATCommand("AT+CMGF=1\r\n", 1000);
//		send_ATCommand("AT+CMGS=+34649103025\r\n", 1000);
//		send_ATCommand("ieeeeeee\r\n", 1000);
//		send_ATCommand("\1a", 1000);
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSI48)
 *            SYSCLK(Hz)                     = 48000000
 *            HCLK(Hz)                       = 48000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            HSI Frequency(Hz)              = 48000000
 *            PREDIV                         = 2
 *            PLLMUL                         = 2
 *            Flash Latency(WS)              = 1
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Select HSI48 Oscillator as PLL source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

