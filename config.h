/**
  ******************************************************************************
  * @file       config.h
  * @author     Dzusan
  * @version    alpha
  * @date       29-November-2014
  * @contractor Claustrophobia
  * @brief      DeviceNet
  * @purpose    Master
  ******************************************************************************
  */


#ifndef CONFIG_H_
#define CONFIG_H_

/* Default factory node address. Can be changed by user command. */
#define DEFAULT_NODE_ADDRESS 0xEA

/* USART baud rate */
#define BAUD_RATE 57600

/* Minimal time of idle on bus between USART frames
 * in single Modbus RTU frame. Practically, after this time,
 * received Modbus frame begin to parse.
 * It's specified in USART bit times. 11bits * 1.5symbols = 17
 */
#define IDLE_BETWEEN_FRAMES 17

/* Maximal number of storable events */
#define SYSTEM_LOG_SIZE_MAX 10

/* Possible events in system. */
enum EventCode
{
	NOTHING_event,
	MB_REQUEST_FRAME_BAD_event,
	MB_REQUEST_RECEIVED_event,
	MB_RESPONSE_READY_event,
	MB_RESPONSE_SENT_event
};

/* __ Available Modbus functions __ */

#define READ_HOLDING_REGISTERS     0x03
/* Specified in  Mosbus RTU V1.1b3 */

#define PRESET_MULTIPLE_REGISTERS  0x10
/* Specified in  Mosbus RTU V1.1b3 */

#define SET_NODE_ADDRESS           0x46
/* Request data:  [New node address]
 * Response data: [New node address]
 */
#define GET_SYSTEM_LOG             0x47
/* Request data:  [Nothing]
 * Response data: [Byte counter | Event 1 code | ... | Event N code]
 */

#endif /* CONFIG_H_ */
