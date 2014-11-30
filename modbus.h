/**
  ******************************************************************************
  * @file       modbus.h
  * @author     Dzusan
  * @version    alpha
  * @date       15-November-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */

#ifndef MODBUS_H_
#define MODBUS_H_

uint8_t SetNodeAddressModbusFunc(struct ModbusADUbuffer *PDUbyte);
uint8_t GetSystemLogModbusFunc(struct ModbusADUbuffer *PDUbyte);
uint8_t ReadHoldingRegistersModbusFunc(struct ModbusADUbuffer *PDUstart);
uint8_t PresetMultipleRegistersModbusFunc(struct ModbusADUbuffer *PDUstart);


#endif /* MODBUS_H_ */
