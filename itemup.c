#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "button.h"
#include <sys/msg.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
static int returnValue =0;
int itemup()
{
	int a;
	int b;
	int fditemup;
	char buf[1024];
	int fdpower;
	off_t newpos;
	ssize_t nread;
	
	srand(time(NULL));

	a=rand()%10;

	char buff[10];
	fditemup=open("itemp.txt",O_RDWR);
	if(fditemup==-1){
		printf("file open error!\n");
		exit(1);
	}
	
	while(nread=read(fditemup,buf,1024)>0){
		lseek(fditemup,(off_t)0,SEEK_CUR);
	}
	lseek(fditemup,(off_t)0,SEEK_SET);
	
	int itemplus=atoi(buf);
	
	textlcd("1","upgrade : %d",itemplus);
    //printf("현재 강화 수 : %d\r\n",itemplus);
    fdpower=open("power.txt",O_RDWR);
	if(fdpower==-1){
		printf("file open error!\n");
		exit(1);
	}
	while(nread=read(fdpower,buf,1024)>0){
		//printf("%s\r\n",buf);
		lseek(fdpower,(off_t)0,SEEK_CUR);
	}
	int power=atoi(buf);
	lseek(fdpower,(off_t)0,SEEK_SET);//power 자리수 buff 자리수 만큼 해주기 malloc
	//char buff=(char*)malloc(자리수*sizeof(char));
	//printf("현재 전투력: %d\r\n",power);
	
	textlcd("2","1. challenge 2. out");
	/*
	while(1){
		buttonInit();
		BUTTON_MSG_T msgRx;
		int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);//메시지큐
		while(1)
		{
			//printf("무엇을 선택하겠는가? ");
			returnValue=msgrcv(msgID,&msgRx,8,0,IPC_NOWAIT);
			if(returnValue>0)
			{
				if((msgRx.keyInput>0)&&(msgRx.pressed>0)){
					switch(msgRx.keyInput)
					{
						case KEY_VOLUMEUP:
										switch(itemplus){
												case 1:
														if(a>=0&&a<=9){
															textlcd("1","SUCCESE !! power+100");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+100;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 2:	
														if(a>=0&&a<=8){
															textlcd("1","SUCCESE !! power+200");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+200;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
														break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 3:
														if(a>=0&&a<=7){
															textlcd("1","SUCCESE !! power+300");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+300;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 4:
														if(a>=0&&a<=6){
															textlcd("1","SUCCESE !! power+400");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+400;
															sprintf(buff,"%d",power);
	 												       write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 5:
														if(a>=0&&a<=5){
															textlcd("1","SUCCESE !! power+500");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+500;
															sprintf(buff,"%d",power);
	   												     write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 6:
														if(a>=0&&a<=4){
															textlcd("1","SUCCESE !! power+600");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+600;
															sprintf(buff,"%d",power);
	  												      write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 7:
														if(a>=0&&a<=3){
															textlcd("1","SUCCESE !! power+700");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+700;
															sprintf(buff,"%d",power);
	     												   write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 8:
														if(a>=0&&a<=2){
															textlcd("1","SUCCESE !! power+800");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+800;
															sprintf(buff,"%d",power);
	    												    write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 9:
															printf("더 이상 강화할수 없습니다.\r\n");
															sleep(1);
															break;
														}
										break;
						case KEY_HOME:
										break;
						case KEY_SEARCH:
										break;
						case KEY_BACK:
										break;
						case KEY_MENU:
										break;
						case KEY_VOLUMEDOWN:
										break;
					}
					break;
				}
			else
			;
			}
		}
	}*/
	//printf("%d\n",a);
	switch(itemplus){
												case 1:
														if(a>=0&&a<=9){
															textlcd("1","SUCCESE !! power+100");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+100;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 2:	
														if(a>=0&&a<=8){
															textlcd("1","SUCCESE !! power+200");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+200;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
														break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 3:
														if(a>=0&&a<=7){
															textlcd("1","SUCCESE !! power+300");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+300;
															sprintf(buff,"%d",power);
															write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 4:
														if(a>=0&&a<=6){
															textlcd("1","SUCCESE !! power+400");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+400;
															sprintf(buff,"%d",power);
	 												       write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 5:
														if(a>=0&&a<=5){
															textlcd("1","SUCCESE !! power+500");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+500;
															sprintf(buff,"%d",power);
	   												     write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 6:
														if(a>=0&&a<=4){
															textlcd("1","SUCCESE !! power+600");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+600;
															sprintf(buff,"%d",power);
	  												      write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 7:
														if(a>=0&&a<=3){
															textlcd("1","SUCCESE !! power+700");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+700;
															sprintf(buff,"%d",power);
	     												   write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 8:
														if(a>=0&&a<=2){
															textlcd("1","SUCCESE !! power+800");
															itemplus++;
															sprintf(buff,"%d",itemplus);
															write(fditemup,buff,sizeof(buff));
															textlcd("2","strengthen : %d",itemplus);
															power=power+800;
															sprintf(buff,"%d",power);
	    												    write(fdpower,buff,sizeof(buff));
															break;
														}
														else{
															textlcd("1","fail");
															break;
														}
		
														case 9:
															printf("더 이상 강화할수 없습니다.\r\n");
															sleep(1);
															break;
														}
	close(fditemup);
	close(fdpower);
	return 0;

}
