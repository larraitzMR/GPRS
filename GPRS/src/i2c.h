/*
 * i2c.h
 *
 *  Created on: 21 jun. 2017
 *      Author: Larraitz
 */

#define I2C_ADDRESS     0x30
#define I2C_TIMING      0x2000090E //0x00A51314

void I2C_Config();
void I2C1_Init(void);
