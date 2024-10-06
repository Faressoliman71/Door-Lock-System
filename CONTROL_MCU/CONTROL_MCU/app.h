
#include "StdTypes.h"
#define opening_code 'o'
#define closing_code 'c'
#define passlength 5
#define NOT_VALID '*'
void uart_receive_handler (void);

/*Function to check the password if it matches the one stored in the memory*/
u8 checkPasswordInMemory(void);

/*Function to save the password in the EEPROM through the I2C*/
void passwordSaving(u8* password);

u8 checkPassword(u8* firstPasswordEntry, u8* secondPasswordEntry);

void countTimerTicks(void);
