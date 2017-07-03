/*
 * i2c.c
 *
 *  Created on: 21 jun. 2017
 *      Author: Larraitz
 */

#include "main.h"
#include "i2c.h"

I2C_HandleTypeDef hi2c1;

void I2C_Config() {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/**I2C1 GPIO Configuration
	 PB6     ------> I2C1_SCL
	 PB7     ------> I2C1_SDA
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_6 ;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* I2C1 init function */
void I2C1_Init(void) {

	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing =  I2C_TIMING;
	hi2c1.Init.OwnAddress1 =  I2C_ADDRESS;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	HAL_I2C_Init(&hi2c1);

	/**Configure Analogue filter
	 */
	HAL_I2CEx_AnalogFilter_Config(&hi2c1, I2C_ANALOGFILTER_ENABLED);

}
