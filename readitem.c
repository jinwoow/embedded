#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int item(void)
{
	int fditem;
	char buf[1];
	off_t newpos;
	ssize_t nread;
	fditem=open("item.txt",O_RDONLY);
	if(fditem==-1){
		printf("file open error!\n");
		exit(1);
	}
	printf("착용 장비 : ");
	while(nread=read(fditem,buf,1)>0){
      printf("%s",buf);
      lseek(fditem,(off_t)0,SEEK_CUR);
      
   }
	lseek(fditem,(off_t)0,SEEK_SET);
	close(fditem);
	return 1;
}
