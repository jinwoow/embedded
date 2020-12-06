#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int power()
{
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
	printf("어플 시작시 전투력 : ");
	while(nread=read(fdpower,buf,1024)>0){
		printf("%s\r\n",buf);
		lseek(fdpower,(off_t)0,SEEK_CUR);
	}
	int power=atoi(buf);
	while(1){
		//cnt++;
		sleep(1);
		power++;
		//printf("%d\r\n",power);
		fndDisp(power,0);
		lseek(fdpower,(off_t)0,SEEK_SET);
		sprintf(buff,"%d",power);
	    write(fdpower,buff,sizeof(buff));
	}
	//lseek(fdpower,(off_t)0,SEEK_SET);//power 자리수 buff 자리수 만큼 해주기 malloc
	//char buff=(char*)malloc(자리수*sizeof(char));
	//sprintf(buff,"%d",power);
	//write(fdpower,buff,sizeof(buff));
	close(fdpower);
	return 1;
}
