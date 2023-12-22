
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_
/**********************************KeyPad Matrix Config **********************************/
 #define COLS 4
 #define ROWS 4

/***********************************Symbols ON BUTTONS CONFIGURE*****************/
#ifdef KEYPAD_C

const u8 Keypad_array[ROWS][COLS]={
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'},
};

									   
#endif 

/*********************************** OUTPUT AND INPUTS PINS CONFIGURE*****************/
#define KEYPAD_FIRST_OUTPUT PINB4
#define KEYPAD_FIRST_INTPUT PIND2
#define NOT_KEY 'T'                // If there is no button pressed

#endif /* KEYPAD_CFG_H_ */