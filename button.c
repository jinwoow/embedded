#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "button.h"
#define INPUT_DEVICE_LIST "/dev/int/event"
#define PROBE_FILE "proc/bus/input/devices"

structBUTTON_MSG_T MSG;

int buttonInit(void)
{
	if (probeButtonPath(buttonPath) == 0)
		return 0;
	fd= open (buttonPath, O_RDONLY);
	msgID =msgget (MESSAGE_ID, IPC_CREAT|0666);
	pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
	return 1;
}
int buttonThFunc(void)
{
	while(1){
	sleep(1);
	msgsnd(msgID,&BUTTON_MSG_T,sizeof(MSG.keyinput),0);
			}
}
