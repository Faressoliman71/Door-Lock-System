#include "Utils.h"
#include "DIO_interface.h"
#include "StdTypes.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"

void MOTOR_stop(MOTOR_TYPE motor)
{
	if(motor>NUNMBERS_OF_MOTORS)
	{
		return;
	}
	DIO_wright_pin(motor_pins_array[motor][IN1],LOW);
	DIO_wright_pin(motor_pins_array[motor][IN2],LOW);
}
void MOTOR_clockwise(MOTOR_TYPE motor)
{
	if(motor>NUNMBERS_OF_MOTORS)
	{
		return;
	}
	DIO_wright_pin(motor_pins_array[motor][IN1],LOW);
	DIO_wright_pin(motor_pins_array[motor][IN2],HIGH);
}
void MOTOR_counter_clockwise(MOTOR_TYPE motor)
{
	if(motor>NUNMBERS_OF_MOTORS)
	{
		return;
	}
	DIO_wright_pin(motor_pins_array[motor][IN1],HIGH);
	DIO_wright_pin(motor_pins_array[motor][IN2],LOW);
}
