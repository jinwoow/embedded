#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "myProject.h"

#define SIZE 201

#define MUTEX_ENABLE 0
int ready;
char buffer[SIZE];
pthread_t thread_object_1;
pthread_t thread_object_2;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    power();
}

void* DoSomeThing(void *arg)
{
	int a;
	int fdpower;
	char buf[1024];
	off_t newpos;
	ssize_t nread;
	int cnt=0;
	char buff[10];
	fdpower=open("power.txt",O_RDWR);
	if(fdpower==-1){
		printf("file open error!\n");
		exit(1);
	}
	lseek(fdpower,(off_t)0,SEEK_SET);
	//printf("1: 장비강화\r\n");
	//printf("2: 종료\r\n");
    while(1){
		printf("1: 장비강화\r\n");
	    printf("2: 종료\r\n");
		printf("무엇을 선택하겠는가? ");
		scanf("%d",&a);
        if(a==1){
            itemup();
        }
        else if(a==2){
			printf("프로그램을 종료합니다\r\n");
			printf("어플 종료시 전투력 : ");
	        while(nread=read(fdpower,buf,1024)>0){
		    printf("%s\r\n",buf);
		    lseek(fdpower,(off_t)0,SEEK_CUR);
	        }
            exit(0);
        }
    }
}
 

int main(void)
{
	item();
	itemp();
	printf("\r\n");
	int err;
    while(1)
    {
        err=pthread_create(&(thread_object_1),NULL,&DoSomeThing,NULL);
        if(err!=0)
            printf("Thread1 Create Error:[%d]\n",err);
        err=pthread_create(&(thread_object_2),NULL,&doSomeThing,NULL);
        if(err!=0)
            printf("Thread2 Create Error:[%d]\n",err);
        pthread_join (thread_object_1,NULL);
        pthread_join (thread_object_1,NULL);
   }
	return 0;
}
