/**
  ******************************************************************************
  * @file       applib.h
  * @author     Dzusan
  * @version    alpha
  * @date       07-November-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */

#ifndef APPLIB_H_
#define APPLIB_H_

uint8_t AddModbusADU(uint8_t val);
uint8_t CRC16check(void);
uint8_t CRC16Add(void);
uint8_t ClearModbusADU(void);
uint8_t SendModbusADU(void);
uint8_t AddSystemLog(uint8_t val);
uint8_t InitSystemLog(void);
uint8_t RemoveFromItemModbusADU(struct ModbusADUbuffer *item);

#endif /* APPLIB_H_ */
