#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "button.h"
#define INPUT_DEVICE_LIST "/dev/int/event"
#define PROBE_FILE "proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N:NAME=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H:Handlers =kbd event"
#define INPUT_DEVICE_LIST "dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define MUTEX_ENABLE 0
pthread_t buttonTH_id;
pthread_mutex_t lockinput;

void *dosomething(void *arg)
{
  	pthread_mutex_lock(&lockinput);
  	struct input_event stEvent;
  	BUTTON_MSG_T TxData;
	int fp;
	while(1){
	int returnValue =0;
	int readsize = read(fp, &stEvent, sizeof(stEvent));
	if( stEvent.type == EV_KEY)
	{
		int msgID= msgget((key_t)MESSAGE_ID,IPC_CREAT|0666);
		TxData.keyinput=stEvent.code;
		TxData.pressed=stEvent.value;
    	msgsnd(msgID, &TxData,8,0);
    	printf("EV_KEY()");
	    switch(stEvent.code)
		{
		case KEY_VOLUMEUP: printf("volume up key):"); break;
		case KEY_HOME: printf("home key):"); break;
		case KEY_SEARCH: printf("search key):"); break;
		case KEY_BACK: printf("back key):"); break;
		case KEY_MENU: printf("menu key):"); break;
		case KEY_VOLUMEDOWN: printf("volume down key):"); break;
		}
	if (stEvent.value ) printf ("pressed\n");
	else printf("released\n");
	}
	pthread_mutex_unlock(&lockinput);
	close(fp);
}
}

int probeButtonPath(char *newPath){
	int returnValue =0;
	int number =0;
	FILE*fp = fopen(PROBE_FILE, "rt");
	while (!feof(fp))
	{
		char tmpstr[200];
		fgets(tmpstr, 200, fp);
		if(strcmp(tmpstr,HAVE_TO_FIND_1) ==0)
		{
			printf("eee found: %s\r\n", tmpstr);
			returnValue =1;
		}
	if((returnValue ==1)&&(strncasecmp(tmpstr,HAVE_TO_FIND_2,strlen(HAVE_TO_FIND_2))==0))
			{
			printf("-->%s", tmpstr);
			printf("\t%c\r\n", tmpstr[strlen(tmpstr) -3]);
			number = tmpstr[strlen(tmpstr)-3]-'0';
			break;
			}
			fclose(fp);
			if (returnValue==1)
			sprintf(newPath, "%s%d",INPUT_DEVICE_LIST,number);
			return returnValue;
			}
}

int buttonInit(void)
{
    int fp;
    int fd;
    int readSize, inputIndex;
    char inputDevPath[200]={0,};
    if( probeButtonPath(inputDevPath) ==0)
    {
        printf("error\r\n");
        printf("did you insmod?\r\n");
        return 0;
    }//경로 찾기
	fp = open(inputDevPath,O_RDONLY);
	pthread_create(&buttonTH_id, NULL,&dosomething,NULL);
	return 1;
}

int buttonstatus(void){

}

int buttonExit(void){
	pthread_join(buttonTH_id,NULL);
}
