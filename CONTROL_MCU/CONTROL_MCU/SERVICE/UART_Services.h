

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_


void UART_SendString(u8* data);
void UART_ReciveString(u8*);


u32 UART_ReceiveNumber(void);
void UART_SendNumber(u32 num);


u8 endian_check(void);
u32 endian_convert(u32 num);


void UART_SendStringCheckSum(u8* str);
u8 UART_ReciveStringCheckSum(u8* str);

#endif /* UART_SERVICES_H_ */