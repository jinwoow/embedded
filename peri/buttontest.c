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

#define INPUT_DEVICE_LIST "dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"

#define INPUT_DEVICE_LIST "/dev/int/event"
#define PROBE_FILE "proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N:NAME=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H:Handlers =kbd event"

int main(int argc, char *argv[])
{
	char inputDevPath[200]={0,};
	int fp;
    BUTTON_MSG_T RxData;
	while(1){
		buttonInit();
		int readsize;
	    int returnValue =0;
	    int msgID= msgget((key_t)MESSAGE_ID,IPC_CREAT|0666);
    	returnValue= msgrcv(msgID,&RxData,sizeof(RxData.keyinput),0,IPC_NOWAIT);
    	if(returnValue){
			buttonInit();
		}
	}
}
