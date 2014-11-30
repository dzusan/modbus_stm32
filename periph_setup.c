/**
  ******************************************************************************
  * @file       periph_setup.c
  * @author     Dzusan
  * @version    alpha
  * @date       04-October-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */
	
/* Includes -----------------------------------------------------------------*/
#include "utils.h"

void SetupConverter(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Converter direction */

	/* Disable default hardware function on PF0 */
	RCC_HSEConfig(RCC_HSE_OFF);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOF , &GPIO_InitStructure); 

	/* Converter channels */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	/* #1 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #2 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #3 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #4 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #5 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #6 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #7 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	/* #8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
}

void SetupLED(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
/*====================REV.1====================================================*/
/*	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA , &GPIO_InitStructure);*/
/*==============================================================================*/

/*====================REV.2====================================================*/
	/* Disable default hardware function on PF1 */
	RCC_HSEConfig(RCC_HSE_OFF);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOF , &GPIO_InitStructure);
/*==============================================================================*/
}

void SetupUSART(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
		/* Enable GPIOA clock                                                   */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); //PA9 to TX USART1
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1); //PA10 to RX USART1

		/* Configure USART1 Rx (PA10) as input floating                         */
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* Configure USART3 Tx (PA9) as alternate function push-pull            */
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

/*====================REV.2====================================================*/
		/* Configure USART1 Transceive enable (PA7) push-pull out               */
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
/*==============================================================================*/
		
/*====================REV.1====================================================*/
/*		 Enable GPIOB clock
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

		GPIO_DeInit(GPIOB);		
		
		 Configure USART1 Transceive enable (PB1) push-pull out
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
		GPIO_Init(GPIOB, &GPIO_InitStructure); */
/*==============================================================================*/

		/* Enable USART1 clock                                                   */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		USART_InitStructure.USART_BaudRate            = BAUD_RATE;
		USART_InitStructure.USART_WordLength          = USART_WordLength_9b;
		USART_InitStructure.USART_StopBits            = USART_StopBits_1;
		USART_InitStructure.USART_Parity              = USART_Parity_Even;
		USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

		USART_Init(USART1, &USART_InitStructure);

		/* Address detection */
		USART_SetAddress(USART1, nodeAddress);
		USART_MuteModeWakeUpConfig(USART1, USART_WakeUp_AddressMark);
		USART_MuteModeCmd(USART1, ENABLE);
		USART_AddressDetectionConfig(USART1, USART_AddressLength_7b);

		/* Idle (end of the ADU) detection */
		USART_SetReceiverTimeOut(USART1, IDLE_BETWEEN_FRAMES);
		USART_ReceiverTimeOutCmd(USART1, ENABLE);

		USART_Cmd(USART1, ENABLE);

		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART1, USART_IT_RTO, ENABLE);
		/* If the flag is not reset, after interrupt enable, this one occurs! */
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);
}


void Setup_USART_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void Setup_TIM_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void SetupTIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	
	/* Master request */
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;
	TIM_TimeBaseInitStructure.TIM_Period = 6;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	/* Long start light */
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;
	TIM_TimeBaseInitStructure.TIM_Period = 160;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	TIM_DeInit(TIM14);
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStructure);
	
	/* Timeout */
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;
	TIM_TimeBaseInitStructure.TIM_Period = 2;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
	TIM_DeInit(TIM16);
	TIM_TimeBaseInit(TIM16, &TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);
}
