#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <sys/stat.h>
#include <pthread.h>
#include "button.h"
#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices "
#define MESSAGE_ID 1122
static int returnValue =0;
int main(void)
{
	buttonInit();
	BUTTON_MSG_T msgRx;
	int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);//메시지큐
	while(1)
	{
	returnValue=msgrcv(msgID,&msgRx,8,0,IPC_NOWAIT);
	if(returnValue>0)
	{
		if((msgRx.keyInput>0)&&(msgRx.pressed>0)){
			switch(msgRx.keyInput)
			{
				case KEY_VOLUMEUP: printf("Volume up key:"); break;
				case KEY_HOME: printf("Home key:"); break;
				case KEY_SEARCH: printf("Search key:"); break;
				case KEY_BACK: printf("Back key:"); break;
				case KEY_MENU: printf("Menu key:"); break;
				case KEY_VOLUMEDOWN: printf("Volume down key:"); break;
			}
			if(msgRx.pressed)
				printf("pressed\n\r");
		}
		else
			{
				printf("relesed\n");
				msgRx.keyInput=0;
				returnValue=0;
			}
	}
	else
	;
	} 
	return 0;
}
