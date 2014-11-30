/**
  ******************************************************************************
  * @file       periph_setup.h
  * @author     Dzusan
  * @version    alpha
  * @date       04-October-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */
	
#ifndef PERIPH_SETUP_H_
#define PERIPH_SETUP_H_

/* LED */
#define LED_PORT GPIOF
#define LED_PIN GPIO_Pin_1
/* RS-485 Transceive enable */
#define TX_EN_PORT GPIOA
#define TX_EN_PIN GPIO_Pin_7
/* Converter direction */
#define CONV_DIR_PORT GPIOF
#define CONV_DIR_PIN GPIO_Pin_0

void SetupLED(void);
void SetupUSART(void);
void Setup_USART_NVIC(void);
void SetupTIM(void);
void Setup_TIM_NVIC(void);
void SetupConverter(void);

#endif /* PERIPH_SETUP_H_ */
