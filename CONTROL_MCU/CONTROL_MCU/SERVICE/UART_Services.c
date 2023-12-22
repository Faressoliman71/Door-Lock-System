#include "StdTypes.h"
#include "UART.h"
#include "UART_Services.h"



/* synch function */
void UART_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
	UART_Send(13);
}

void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for (;str[i]!=13;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	
	/*u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);*/
}

u32 UART_ReceiveNumber(void)
{
	u32 num=0;
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u8 b4=UART_Receive();
	num=(u32)b1|(u32)b2<<8|(u32)b3<<16|(u32)b4<<24;
	
	return num;
	
	/*u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();*/
}


#define  LITTLE 1
#define  BIG    0

u8 endian_check(void)
{
	u32 x=1;
	u8*p=&x; 
	if (*p==1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 endian_convert(u32 num)
{
	return  (num<<24)|(num>>24)|((num>>8)&(0x0000ff00))|((num<<8)&(0x00ff0000));
}
u16 endian_convert_16(u16 num)
{
	return  (num<<8)|(num>>8);
}

void UART_SendStringCheckSum(u8* str)
{
	u8 l=0;
	u16 sum=0;
	for(l=0;str[l];l++);
	UART_Send(l);   //len send 
	for(l=0;str[l];l++)
	{
		UART_Send(str[l]);  //data send
		sum=sum+str[l];
	}
	UART_Send((u8)(sum));   //sum of data send
	UART_Send((u8)(sum>>8));
}

u8 UART_ReciveStringCheckSum(u8* str)
{
	 u8 i,b0,b1;
	 u16 sum_cal=0,sum; 
	 u8 len=UART_Recive();
	 for(i=0;i<len;i++)
	 {
		 str[i]=UART_Recive();
		 sum_cal=sum_cal+str[i];
	 }
	 str[i]=0;
	 b0=UART_Receive();
	 b1=UART_Receive();
	 sum_cal=(u16)b0|(u16)(b1<<8);
	 if(sum==sum_cal)
	 {
		 return 1; //data is correct
	 }
	 else
	 {
		  return 0; //data is not correct
	 }
}

/****************************Ayschronous Fun********************************/
u8 *str_copy;
 void send_data(void)
 {
	 static u8 i=1;
	 UART_SendByteNoBlock(str_copy[i]);
	 i++;
 }

 void UART_send_string_AysFun(u8 *str)
 {
	 UART_TX_InterruptEnable();
	 UART_TX_SetCallBack(send_data);
	 UART_SendByteNoBlock(str[0]);
	 str_copy=str;
 }




