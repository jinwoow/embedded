#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int itemp()
{
	int fditemp;
	char buf[10];
	off_t newpos;
	ssize_t nread;
	fditemp=open("itemp.txt",O_RDONLY);
	if(fditemp==-1){
		printf("fd itemp file open error!\n");
		exit(1);
	}
	printf("현재 강화된 수 : ");
	while(nread=read(fditemp,buf,1)>0){
		printf("%s",buf);
		lseek(fditemp,(off_t)0,SEEK_CUR);
	}
	close(fditemp);
	return 1;
}

