#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_ID 1122
typedef struct
{
	long int messageNum;
	int keyinput;
	int pressed;
} BUTTON_MSG_T;

int buttonInit(void);
int buttonThFunc(void);
int buttonExit(void);
#endif


