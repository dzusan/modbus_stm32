/**
  ******************************************************************************
  * @file       applib.c
  * @author     Dzusan
  * @version    alpha
  * @date       07-November-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "utils.h"

uint8_t InitSystemLog(void)
{
	AddSystemLog(NOTHING_event);
	currentSystemLog = firstSystemLog;

	return 0;
}

uint8_t AddSystemLog(uint8_t val)
{
	struct SystemLog *item;
	item = (struct SystemLog *)malloc(sizeof(struct SystemLog));
	if(!item) return 1;          /* End of RAM */
	item->event = val;
	item->next = NULL;

	if(!lastSystemLog)      /* First item */
		firstSystemLog = item;
	else
		lastSystemLog->next = item;

	lastSystemLog = item;

	/* Shift system log queue if it's full */
	if(countSystemLog > SYSTEM_LOG_SIZE_MAX)
	{
		item = firstSystemLog;
		firstSystemLog = item->next;
		free(item);

	}
	else
		countSystemLog++;

	return 0;
}

uint8_t SendModbusADU(void)
{
	struct ModbusADUbuffer *item = firstModbusADUbuffer;

	if(item)
	{
		USART_SendData(USART1, item->data);
		firstModbusADUbuffer = item->next;
		free(item);
		countModbusADUbuffer--;
		return 0;
	}
	else
	{
		lastModbusADUbuffer = NULL;
		return 1;
	}
}

uint8_t AddModbusADU(uint8_t val)
{
	struct ModbusADUbuffer *item;
	item = (struct ModbusADUbuffer *)malloc(sizeof(struct ModbusADUbuffer));
	if(!item) return 1;          /* End of RAM */
	item->data = val;
	item->next = NULL;

	if(!lastModbusADUbuffer)      /* First item */
		firstModbusADUbuffer = item;
	else
		lastModbusADUbuffer->next = item;

	lastModbusADUbuffer = item;
	countModbusADUbuffer++;

	return 0;
}

uint8_t CRC16check(void)
{
	struct ModbusADUbuffer *item;
	item = firstModbusADUbuffer;
	uint8_t uchCRCHi = 0xFF;  /*high byte of CRC initialized*/
	uint8_t uchCRCLo = 0xFF;  /*low byte of CRC initialized*/
	uint8_t msgCRCLo;
	uint8_t msgCRCHi;
	unsigned uIndex ;  /*will index into CRC lookup table*/
	int count;

	for(count = countModbusADUbuffer; count > 1; count--)
	{
		uIndex = uchCRCLo ^ item->data ;  /*calculate the CRC*/
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
		uchCRCHi = auchCRCLo[uIndex] ;

		item = item->next;
	}
	msgCRCLo = item->data;
	item = item->next;
	msgCRCHi = item->data;

	if(msgCRCLo == uchCRCLo && msgCRCHi == uchCRCHi)
		return 0;
	else
		return 1;
}

uint8_t CRC16Add(void)
{
	struct ModbusADUbuffer *item;
	item = firstModbusADUbuffer;
	uint8_t uchCRCHi = 0xFF;  /*high byte of CRC initialized*/
	uint8_t uchCRCLo = 0xFF;  /*low byte of CRC initialized*/
	unsigned uIndex ;  /*will index into CRC lookup table*/
	int count;

	while(item)
	{
		uIndex = uchCRCLo ^ item->data ;  /*calculate the CRC*/
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
		uchCRCHi = auchCRCLo[uIndex] ;

		item = item->next;
	}

	AddModbusADU(uchCRCLo);
	AddModbusADU(uchCRCHi);

	return 0;

}

uint8_t ClearModbusADU(void)
{
	struct ModbusADUbuffer *first = firstModbusADUbuffer;
	struct ModbusADUbuffer *second = firstModbusADUbuffer->next;

	while(countModbusADUbuffer)
	{
		free(first);
		first = second;
		second = second->next;
		countModbusADUbuffer--;
	}

	lastModbusADUbuffer = NULL;

	return 0;
}

uint8_t RemoveFromItemModbusADU(struct ModbusADUbuffer *item)
{
	struct ModbusADUbuffer *delete;

	lastModbusADUbuffer = item;
	delete = item->next;
	item = delete->next;
	while(item)
	{
		free(delete);
		countModbusADUbuffer--;
		delete = item;
		item = item->next;
	}
	free(delete);
	countModbusADUbuffer--;

	lastModbusADUbuffer->next = NULL;

	return 0;
}
