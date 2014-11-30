/**
  ******************************************************************************
  * @file       main.c
  * @author     Dzusan
  * @version    alpha
  * @date       04-October-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */
		
#include "utils.h"

int main()
{	
	InitSystemLog();

	SetupLED();
	SetupUSART();
	Setup_USART_NVIC();
	//SetupConverter();

	/* Here is a task manager.
	 * It is reading system log sequentially and making a decision. */
	while(1)
	{
		switch(currentSystemLog->event)
		{
			case NOTHING_event:
				break;
			case MB_REQUEST_FRAME_BAD_event:
				break;
			case MB_REQUEST_RECEIVED_event:
				ADU_handler();
				break;
			case MB_RESPONSE_READY_event:
				GPIO_WriteBit(TX_EN_PORT, TX_EN_PIN, Bit_SET); /* Transmitting enable */
				SendModbusADU();
				break;
			case MB_RESPONSE_SENT_event:
				GPIO_WriteBit(TX_EN_PORT, TX_EN_PIN, Bit_RESET); /* Transmitting disable */
				break;
			default:
				GPIO_WriteBit(LED_PORT, LED_PIN, registersTable[4] & 1);
		}
		/* Wait for the next event */
		while(!currentSystemLog->next);
		/* Jump to the next event */
		currentSystemLog = currentSystemLog->next;
	}
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		AddModbusADU((uint8_t)USART_ReceiveData(USART1));
		USART_MuteModeCmd(USART1, DISABLE);
	}

	if(USART_GetITStatus(USART1, USART_IT_RTO))
	{
		USART_ClearITPendingBit(USART1, USART_IT_RTO);
		USART_MuteModeCmd(USART1, ENABLE);
		AddSystemLog(MB_REQUEST_RECEIVED_event);
	}

	if(USART_GetITStatus(USART1, USART_IT_TC))
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		if(SendModbusADU())
			AddSystemLog(MB_RESPONSE_SENT_event);
	}
}
