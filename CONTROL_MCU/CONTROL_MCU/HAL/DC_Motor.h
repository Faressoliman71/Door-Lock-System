
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "StdTypes.h"

typedef enum
{
	 CW ,
	 A_CW,
	 Stop
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,u8 speed);
#endif /* DC_MOTOR_H_ */



