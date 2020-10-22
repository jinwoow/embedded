#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "mymessage.h"
#include <sys/msg.h>

int main(void)
{	
	int shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(shmid ==-1)	//만약 에러가 났다면
	{
		printf("shmget error왜 안되는지 모르겠어요\r\n");	//이렇게 출력
		return 1;
	}

	char *shmemAddr;	//공유메모리에 접근할 포인터변수
	shmemAddr= shmat(shmid, (void*)NULL,0);	//설정하고 포인터에 연결
	if( ((int)(shmemAddr))== -1)	//만약 포인터가 에러가 났으면
	{
		printf("shmat error교수님 도저히 모르겠어요 \r\n");	//이렇게 출력
		return -2;
	}
	structmymsg messagetxdata;	//구조체 변수설정하기
	int msgqueue = msgget((key_t)MY_MESSAGE_ID,IPC_CREAT|0666);//메세지 초기설정해주기

	if (msgqueue == -1)	//에러가 났으면
	{
		printf ("살려주세요 교수님 제바류ㅠ\r\n");	//이렇게 출력
		return -1;
	}
	while(1)
	{
	sleep(1);
	*((int *)shmemAddr)= rand(); //메모리에 랜덤함수로 랜덤값 입력
	snprintf(messagetxdata.piggyback, sizeof(messagetxdata.piggyback)-1,
			"hello! this is %d message",*((int*)shmemAddr));//구조체안에 메세지 삽입
	messagetxdata.messagetype =1;	//1이 적당
	printf("\tsending %d message\r\n",*((int*)shmemAddr));	//여기에 값 출력
	msgsnd(msgqueue, &messagetxdata, sizeof(messagetxdata.piggyback), 0);//전송하기
	
	}


}
