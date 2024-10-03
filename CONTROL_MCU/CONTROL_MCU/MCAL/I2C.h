


#ifndef I2C_H_
#define I2C_H_
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

/*I2C status bits -> TWSR Register*/

#define TWI_START             0x08 /*Start condition has been sent*/
#define TWI_REP_START    0x10 /*repeated start condition has been sent*/

/*1. Master Transmitter Mode*/
#define TWI_MT_SLA_W_ACK      0x18 /*Master transmits Slave Address + Write Bit and receives Acknowledgment*/
#define TWI_MT_SLA_W_NACK     0x20 /*Master transmits Slave Address + Write Bit and receives NOT Acknowledgment*/
#define TWI_MT_DATA_ACK       0x28 /*Master transmits data and Acknowledgment is received*/
#define TWI_MT_DATA_NACK      0x30 /*Master transmits data and NOT Acknowledgment is received*/

/*2. Master Receiver Mode*/
#define TWI_MR_SLA_R_NACK     0x38 /*Master transmits Slave Address + Read Bit and receives NOT Acknowledgment*/
#define TWI_MT_SLA_R_ACK      0x40 /*Master transmits Slave Address + Read Bit and receives Acknowledgment*/
#define TWI_MR_DATA_ACK       0x50 /*Master receives data and send Acknowledgment to slave*/
#define TWI_MR_DATA_NACK      0x58 /*Master receives data and send NOT Acknowledgment to slave*/




void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(u8 data);
u8 TWI_readByteWithACK(void);
u8 TWI_readByteWithNACK(void);
u8 TWI_getStatus(void);



#endif /* I2C_H_ */