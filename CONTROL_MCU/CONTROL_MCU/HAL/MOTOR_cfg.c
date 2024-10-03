#include "DIO_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"

const DIO_PIN_TYPE motor_pins_array[NUNMBERS_OF_MOTORS][NUNMBERS_OF_PINS_PER_MOTOR]={
	              /*IN 1    IN 2*/
	/*MOTOR1*/   { M1_IN1,M1_IN2},
	/*MOTOR2*/   { M2_IN1,M2_IN2},
	/*MOTOR3*/   { M3_IN1,M3_IN2},
	/*MOTOR4*/   { M4_IN1,M4_IN2}
};