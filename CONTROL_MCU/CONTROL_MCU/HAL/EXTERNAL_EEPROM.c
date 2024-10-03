#include "EXTERNAL_EEPROM.h"
#include "I2C.h"
#include <util/delay.h>

u8 EEPROM_writeByte(u16 address,u8 byte)
{
	_delay_ms(10);
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	return ERROR;

	TWI_writeByte( (u8)(((address&0x0700)>>7) | (0xA0)) );
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	return ERROR;

	TWI_writeByte((u8)address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	return ERROR;

	TWI_writeByte(byte);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	return ERROR;

	TWI_stop();

	return SUCCESS;
}

u8 EEPROM_readByte(u16 address,u8 *value)
{
	_delay_ms(10);
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	return ERROR;

	TWI_writeByte( (u8)((address&0x0700)>>7 | (0xA0)) );
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	return ERROR;

	TWI_writeByte((u8)address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	return ERROR;

	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
	return ERROR;

	TWI_writeByte((u8)((0xA0) | ((address & 0x0700)>>7) | 1));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
	return ERROR;

	*value = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
	return ERROR;

	TWI_stop();
	return SUCCESS;
}