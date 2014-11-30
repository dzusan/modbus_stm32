/**
  ******************************************************************************
  * @file       utils.h
  * @author     Dzusan
  * @version    alpha
  * @date       04-October-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */


#ifndef UTILS_H_
#define UTILS_H_

/* System Includes -----------------------------------------------------------*/
#include <sys/types.h>
#include "stm32F0xx_conf.h"

extern volatile uint8_t nodeAddress;

/* Tables of CRC values */
extern const uint8_t auchCRCHi[256];
extern const uint8_t auchCRCLo[256];

/* Modbus ADU buffer */
struct ModbusADUbuffer
{
	volatile uint8_t data;
	struct ModbusADUbuffer *next;
};
extern volatile struct ModbusADUbuffer *firstModbusADUbuffer;
extern volatile struct ModbusADUbuffer *lastModbusADUbuffer;
/* The counter is needed for the CRC16check() only.
 * It detect two last CRC bytes. */
extern volatile uint8_t countModbusADUbuffer;

/* Modbus data model Registers table */
extern volatile uint16_t registersTable[20];

/* System log */
extern volatile uint8_t countSystemLog;

struct SystemLog
{
	volatile uint8_t event;
	struct SystemLog *next;
};
extern volatile struct SystemLog *firstSystemLog;
extern volatile struct SystemLog *lastSystemLog;
extern volatile struct SystemLog *currentSystemLog;

/* Project Includes ----------------------------------------------------------*/
#include "config.h"
#include "periph_setup.h"
#include "applib.h"
#include "handlers.h"
#include "modbus.h"

#endif /* UTILS_H_ */
