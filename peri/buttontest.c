#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "button.h"
#include <sys/ipc.h>

int main(int argc, char *argv[])
{
    struct input_event stEvent;
    BUTTON_MSG_T RxData;
	while(1){
		buttonInit();
		int readsize;
	    int returnValue =0;
	    int msgID= msgget((key_t)MESSAGE_ID,IPC_CREAT|0666);
    	returnValue= msgrcv(msgID,&RxData,8,0,IPC_NOWAIT);
    	if(returnValue){
			printf("EV_KEY()");
		}
	}
}
