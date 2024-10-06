#include "MemMap.h"
#include "LCD_interface.h"
#include "KeyPad_interface.h"
#include "UART.h"
#include "UART_Services.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Application.h"
#include "DIO_interface.h"
#include <util/delay.h> 



#define PassLength 5
#define ENTER '='
#define NOT_VALID '*'
#define NOT_KEY 'T'
u8 pass1 [PassLength] ;
u8 pass2 [PassLength] ;
u8 check = 0 ;
u8 flag = 0 ;
u8 option = 0 ;
u8 received_char ;


int main(void)
{
	
	DIO_init_all_pins();
    LCD_init();
	KEYPAD_in_it();
	UART_Init();
	sei();
	UART_RX_InterruptEnable();

	
	
	
    while(1) 
    { 
	     while(flag == 0)
	     {
		  get_password();
		  check = check_password();
		  if(check)
		  {
			  LCD_clear();
			  LCD_write_string("matched");
			  for(int j = 0 ; j<PassLength;j++)
			  {
				  UART_Send(pass1[j]+'0');
				  _delay_ms(10);
			  }
			  flag = 1;
			  _delay_ms(10);
			  LCD_clear();
		  }
		  else 
		  {
			  LCD_clear();
		     LCD_write_string("un matched");
			 _delay_ms(1000);
		
		  }
	  }
	  while ( option == 0)
	  { 
		  
		   LCD_clear();
		   LCD_write_string("+ : open door ");
		   LCD_GoTo(1,0);
		   LCD_write_string("- : change pass ");
		   option = NOT_KEY;
		   while(option == NOT_KEY)
		   {
		     option = KEYPAD_get_key();
		   }
		   if(option == '-')
		   {
			   UART_Send(option);
			  	   
			   get_password();
			     for(int j = 0 ; j<PassLength;j++)
			     {
				     UART_Send(pass1[j]+'0');
					 _delay_ms(10);
			     }
				 option = 0;
		   }
		   else if ( option == '+')
		   {
			  UART_Send(option);
			   LCD_clear();
			   get_password();
			   for(int j = 0 ; j<PassLength;j++)
			   {
				   UART_Send(pass1[j]+'0');
				   _delay_ms(10);
			   }
			   option = 0;
		   }
	  }
	 
	
    }
}

void get_password ()
{ 
    LCD_clear();
	LCD_write_string("plz enter pass") ;
	LCD_GoTo(1,0);
	pass1[PassLength-1]= NOT_VALID;
	 u8 i = 0 ;
	u8 temp = NOT_KEY ;
	while ( pass1[PassLength-1] == NOT_VALID )
	{
		
		while ( temp == NOT_KEY)
		{
			temp = KEYPAD_get_key();
		}
		if (  temp != ENTER)
		{
			pass1 [i] = temp-'0' ;
			LCD_write_string("*");
			temp = NOT_KEY ;
			i++ ;
			
		}
		
	}
	
};
u8 check_password()
{
	LCD_clear();
	LCD_write_string("plz re-enter") ;
	LCD_GoTo(1,0);
	pass2[PassLength-1]= NOT_VALID;
	u8 i = 0 ;
	u8 temp = NOT_KEY ;
	while ( pass2[PassLength-1] == NOT_VALID )
	{
		
		while ( temp == NOT_KEY)
		{
			temp = KEYPAD_get_key();
		}
		if (  temp != ENTER)
		{
			pass2 [i] = temp-'0' ;
			LCD_write_string("*");
			temp = NOT_KEY ;
			i++ ;
			
		}
		
	}
	for ( int j = 0 ; j<PassLength;j++)
	{
		if(pass1[j]!=pass2[j])
		{
			return 0 ;
		}
	}
	return 1 ;
	
};