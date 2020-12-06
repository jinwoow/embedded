#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include "button.h"
#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"
#define MESSAGE_ID 1122

char buttonPath;
static int fd=0;
int msgID=0;
static pthread_t buttonTh_id;
char inputDevPath[200]={0,};


int buttonInit(void)
{
	int count=0;
	
	if(probeButtonPath(inputDevPath)==0)
    {
        printf("error\r\n");
        printf("did you insmod?\r\n");
        return 0;
    }
    fd=open(inputDevPath, O_RDONLY);
    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    while (1)
	{
		int returnValue = 0;
		BUTTON_MSG_T tmpmsg;
		returnValue = msgrcv(msgID, &tmpmsg, sizeof(tmpmsg)-sizeof(long int), 0, IPC_NOWAIT);
		if (returnValue == -1) break; //There is no message at all
			count++;
		printf ("%d message Comes: [%s]\r\n",count, tmpmsg.keyInput);
	}
	printf ("\tI got %d messages in the queue\r\n",count);
//여기까지 Message Queue 예제에서 복붙

    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

int buttonExit(void)
{
   pthread_cancel(&buttonTh_id);
   close(fd);
}

int probeButtonPath(char *newPath)
{
    int returnValue = 0;
    int number = 0;
    FILE *fp = fopen(PROBE_FILE,"rt");
    #define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
    #define HAVE_TO_FIND_2 "H: Handlers=kbd event"
    while(!feof(fp))
    {
        char tmpStr[200];
        fgets(tmpStr,200,fp);
        if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
        {
        //printf("YES! I found!: %s\r\n", tmpStr);
        returnValue = 1;
        }
        if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2,strlen(HAVE_TO_FIND_2)) == 0))
        {
           // printf ("-->%s",tmpStr);
           // printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
            number = tmpStr[strlen(tmpStr)-3] - '0';
            break;
        }
    }
    fclose(fp);
    if (returnValue == 1)
    sprintf (newPath,"%s%d",INPUT_DEVICE_LIST,number);
    return returnValue;
}

static void *buttonThFunc(void*a)
{
   BUTTON_MSG_T msgTx;
   struct input_event stEvent;
   msgTx.messageNum = 1.0;
   //msgTx.keyInput =0; //넣어야되나

   while(1)
   {
      
      read(fd,&stEvent,16);
      //printf("EV_KEY=%d\n\r",EV_KEY);
      //if((stEvent.type==EV_KEY)&&(stEvent.value>0))    //키가눌리면
      if(stEvent.type)
      {
         msgTx.keyInput=stEvent.code;
         msgTx.pressed=stEvent.value;
         msgsnd(msgID,&msgTx,8,0);
      }
      else
      ;
   }
}
