
#include "StdTypes.h"
#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4
	}MOTOR_TYPE;

void MOTOR_stop(MOTOR_TYPE motor);
void MOTOR_clockwise(MOTOR_TYPE motor);
void MOTOR_counter_clockwise(MOTOR_TYPE motor);
//speed 0 to 100% (not complete...)
void MOTOR_speed(MOTOR_TYPE motor,u8 speed);

#endif /* MOTOR_INTERFACE_H_ */