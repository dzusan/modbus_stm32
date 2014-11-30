/**
  ******************************************************************************
  * @file       modbus.c
  * @author     Dzusan
  * @version    alpha
  * @date       15-November-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "utils.h"

uint8_t SetNodeAddressModbusFunc(struct ModbusADUbuffer *PDUbyte)
{
	if(PDUbyte->data & 0x80)
	{
		nodeAddress = PDUbyte->data;

	/* Here is a rain dance with USART:
	 * 1. USART_SetAddress() can only proceed with disabled USART.
	 * 2. After disabling USART the interrupt (USART_IT_TC) occurs.
	 *    For avoiding accident it's necessary to disable global interrupt.
	 * 3. After enabling USART the USART_IT_TC flag sets.
	 *    For avoiding accident it's necessary to reset flag by force.
	 */

		NVIC_DisableIRQ(USART1_IRQn);
		USART_Cmd(USART1, DISABLE);
		USART_SetAddress(USART1, nodeAddress);
		USART_Cmd(USART1, ENABLE);
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		NVIC_EnableIRQ(USART1_IRQn);

		return 0;
	}
	else
		return 1;
}

uint8_t GetSystemLogModbusFunc(struct ModbusADUbuffer *PDUbyte)
{
	struct SystemLog *logByte = firstSystemLog;

	PDUbyte->data = countSystemLog; /* 1 of 2 free slots in ModbusADUbuffer (CRC slots) overwritten */
	PDUbyte = PDUbyte->next;        /* Next byte */
	PDUbyte->data = logByte->event; /* 2 of 2 free slots in ModbusADUbuffer (CRC slots) overwritten */
	logByte = logByte->next;

	/* New slots */
	while(logByte)
	{
		AddModbusADU(logByte->event);
		logByte = logByte->next;
	}
	return 0;
}

uint8_t ReadHoldingRegistersModbusFunc(struct ModbusADUbuffer *PDUstart)
{
	struct ModbusADUbuffer *byte = PDUstart;
	uint16_t addr = 0;
	uint16_t num = 0;
	uint16_t count = 0;

	/* Parcing Modbus PDU */
	addr |= (uint16_t)byte->data << 8; /* [2] Register start address high byte */
	byte = byte->next;                 /* [2] Next byte                        */
	addr |= (uint16_t)byte->data;      /* [3] Register start address low byte  */
	byte = byte->next;                 /* [3] Next byte                        */
	num |= (uint16_t)byte->data << 8;  /* [4] Number of registers high byte    */
	byte = byte->next;                 /* [4] Next byte                        */
	num |= (uint16_t)byte->data;       /* [5] Number of registers low byte     */

	byte = PDUstart;
	byte->data = num * 2;

	if(num * 2 + 3 < countModbusADUbuffer)
	{
		for(count = addr; count < addr + num; count++)
		{
			byte = byte->next;
			byte->data = registersTable[count] >> 8;
			byte = byte->next;
			byte->data = registersTable[count];
		}
		RemoveFromItemModbusADU(byte);
	}
	else
	{
		for(count = addr; count < addr + 2; count++)
		{
			byte = byte->next;
			byte->data = registersTable[count] >> 8;
			byte = byte->next;
			byte->data = registersTable[count];
		}
		RemoveFromItemModbusADU(byte);

		for(; count < addr + num; count++)
		{
			AddModbusADU(registersTable[count] >> 8);
			AddModbusADU(registersTable[count]);
		}
	}

	return 0;
}

uint8_t PresetMultipleRegistersModbusFunc(struct ModbusADUbuffer *PDUstart)
{
	struct ModbusADUbuffer *byte = PDUstart;
	struct ModbusADUbuffer *responseEnd;
	struct ModbusADUbuffer *delete;
	uint16_t addr = 0;
	uint16_t numReg = 0;
	uint16_t numByte = 0;
	uint16_t count = 0;

	/* Parcing Modbus PDU */
	addr |= (uint16_t)byte->data << 8;   /* [2] Register start address high byte */
	byte = byte->next;                   /* [2] Next byte                        */
	addr |= (uint16_t)byte->data;        /* [3] Register start address low byte  */
	byte = byte->next;                   /* [3] Next byte                        */
	numReg |= (uint16_t)byte->data << 8; /* [4] Number of registers high byte    */
	byte = byte->next;                   /* [4] Next byte                        */
	numReg |= (uint16_t)byte->data;      /* [5] Number of registers low byte     */
	responseEnd = byte;                  /* [ ] End of future response           */
	byte = byte->next;                   /* [5] Next byte                        */
	numByte |= (uint16_t)byte->data;     /* [6] Number of registers low byte     */

	for(count = addr; count < addr + numReg; count++)
	{
		registersTable[count] = 0;
		byte = byte->next;
		registersTable[count] |= (uint16_t)byte->data << 8;
		byte = byte->next;
		registersTable[count] |= (uint16_t)byte->data;
	}

	RemoveFromItemModbusADU(responseEnd);

	return 0;
}
