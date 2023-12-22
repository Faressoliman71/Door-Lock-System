
#include "DC_Motor.h"
//#include <avr/io.h>
#include "StdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"


extern void PWM_Timer0_Start(u8 duty_cycle);

void DcMotor_Init(void)
{
      DIO_wright_pin(PIND0,LOW);
      DIO_wright_pin(PIND1,LOW);
}
void DcMotor_Rotate(DcMotor_State state , u8 speed)
{
	switch (state)
	{
		case Stop:
	DIO_wright_pin(PIND0,LOW);
	DIO_wright_pin(PIND1,LOW);
	PWM_Timer0_Start(speed);

		break;

	case CW:
		DIO_wright_pin(PIND0,HIGH);
		DIO_wright_pin(PIND1,LOW);
		PWM_Timer0_Start(speed);

		break;
	case A_CW:
		DIO_wright_pin(PIND0,LOW);
		DIO_wright_pin(PIND1,HIGH);
		PWM_Timer0_Start(speed);
		break;
	}
}
