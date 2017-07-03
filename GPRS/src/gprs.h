/*
 * gprs.h
 *
 *  Created on: 26 jun. 2017
 *      Author: Propietario
 */


void send_ATCommand(char *cmd, uint32_t esp_timeout);
void send_ATCommand_DMA(char *cmd);
void write_command(char *cmd, uint32_t esp_timeout);
void read_buffer(void);
