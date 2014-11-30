/**
  ******************************************************************************
  * @file       handlers.c
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

uint8_t ADU_handler(void)
{
	struct ModbusADUbuffer *start = firstModbusADUbuffer;
	struct ModbusADUbuffer *byte;
	uint16_t count = 0;

	if(!CRC16check())
	{
		if(start->data == nodeAddress)
		{
			start = start->next; /* [0] Skip node address. */
			switch(start->data)  /* [1] Modbus function code. */
			{
				case READ_HOLDING_REGISTERS:
					ReadHoldingRegistersModbusFunc(start->next);
					break;
				case PRESET_MULTIPLE_REGISTERS:
					PresetMultipleRegistersModbusFunc(start->next);
					break;
				case SET_NODE_ADDRESS:
					SetNodeAddressModbusFunc(start->next);
					/* Response fully consists of the request. */
					/* So message ready to send and it's all over. */
					AddSystemLog(MB_RESPONSE_READY_event);
					return 0;
				case GET_SYSTEM_LOG:
					GetSystemLogModbusFunc(start->next);
					break;
				default:
				/* Function not supported. Clear all and exit with code 1. */
					ClearModbusADU();
					return 1;
			}
			CRC16Add();  /* Calculate CRC for assembled message. */
			AddSystemLog(MB_RESPONSE_READY_event); /* Assembled message ready to send. */
		}
		else   /* Broadcast request */
		{
			start = start->next; /* [0] Skip node address. */
			switch(start->data)  /* [1] Modbus function code */
			{
				case 0x10:
					PresetMultipleRegistersModbusFunc(start->next);
					break;
				default:
				/* Function not supported. Clear all and exit with code 1. */
					ClearModbusADU();
					return 1;
			}
			/* Send nothing on broadcast request */
			ClearModbusADU();
		}

		/* Handler done without errors */
		return 0;
	}
	else  /* CRC not matched. Clear all and exit with code 1. */
	{
		ClearModbusADU();
		AddSystemLog(MB_REQUEST_FRAME_BAD_event);
		return 1;
	}
}
