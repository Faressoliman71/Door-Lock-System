
#include "Utils.h"
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_interface.h"
#include "I2C.h"
#include "UART.h"
#include "Timers.h"
#include "MOTOR_interface.h"
#include "EXTERNAL_EEPROM.h"
#include "app.h"
#include <util/delay.h>

u8 first_pass[passlength] ; // to receive pass from hmi 
u8 second_pass [passlength]; // to read pass from EEPROM
u8 count = 0 ;
u8 count2 = 0 ; // to count number of wrong password entered
u8 flag = 0 ; // flag to indicate which password is sent from hmi_mcu
u8 flag2 = 0; // flag to indicate that first password has been saved in EEPROM  
u8 temp ;
u8 option = 0 ;
u8 state_of_second_pass = 0 ;
u16 timerTicks ;



int main(void)
{
	
	DIO_init_all_pins();
	UART_Init();
	TWI_init();
	sei();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(uart_receive_handler);
	
	
	
   
    while (1) 
    {
		if(flag == 1 && flag2 == 0)
		{
			passwordSaving(first_pass);
			flag2 = 1 ;
		}
		switch (option)
		{
			case '+':
			    state_of_second_pass = checkPasswordInMemory();
			    if(state_of_second_pass ==1 && flag == 2)
			     {
				SET_BIT(PORTC,7);
				MOTOR_clockwise(M1);
				_delay_ms(5000);
				CLR_BIT(PORTC,7);
				flag = 1;
			     }
			   else
			    {
				count2++;
			    }
				
			   break;
			case '-' :
			    if(flag == 2)
				{
					passwordSaving(first_pass);
					flag =1 ;
				}
			  
			   break;   
			   
			
		}
	 
		
    }
}


void uart_receive_handler()
{
	
		temp = UDR ;
		switch (temp)
		{
			case '+' :
			   option = temp ;
			    break ;
			case '-' :
			   option = temp ;
			    break;
			default :
			     first_pass[count++] = temp ;
			
		}
		
		if(count == passlength)
		{
			count = 0 ;
			flag++;
		}
		
	
}
void passwordSaving(u8* password)
{
	u8 i = 0, memoryLocationStart = 60; /*store it in a random location inside the EEPROM to avoid hacking*/
	for(i = 0; i < passlength; i++)
	{
		EEPROM_writeByte(memoryLocationStart++,password[i]);
		_delay_ms(10); /*write byte by byte to teh memory*/
	}
}
u8 checkPassword(u8* firstPasswordEntry, u8* secondPasswordEntry)
{
	u8 i = 0, PasswordMatchFlag = 0;
	for(i = 0; i < passlength; i++)
	{
		if (firstPasswordEntry[i] == secondPasswordEntry[i]) /*check each location corresponding to the other one if they are equal*/
		{
			PasswordMatchFlag = 1;
		}
		else
		{
			PasswordMatchFlag = 0; /*if any digit is not the same break from the loop since the 2 passwords do not match*/
			break;
		}
	}
	return PasswordMatchFlag;
}
u8 checkPasswordInMemory(void)
{
	u8 i = 0, memoryLocationStart = 60; /*password is stored in a random location inside the EEPROM to avoid hacking*/
	for(i = 0; i < passlength; i++)
	{
		EEPROM_readByte(memoryLocationStart,&second_pass[i]); /*read the password stored in the memory and save it temporarily*/
		memoryLocationStart++;
		_delay_ms(10);
	}
	return checkPassword(first_pass,second_pass); /*check if the 2 passwords match or not*/
}
void countTimerTicks(void)
{
	timerTicks++;

}
