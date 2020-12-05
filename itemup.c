#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
	
	
    printf("현재 강화 수 : %d\r\n",itemplus);
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
	printf("현재 전투력: %d\r\n",power);
	
    switch(itemplus){
		case 1:
		if(a>=0&&a<=9){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+100;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 2:	
		if(a>=0&&a<=8){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+200;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 3:
		if(a>=0&&a<=7){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+300;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			break;
		}
		
		case 4:
		if(a>=0&&a<=6){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+400;
			printf("장비강화 성공 후전투력: %d\r\n",power);;
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 5:
		if(a>=0&&a<=5){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+500;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 6:
		if(a>=0&&a<=4){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+600;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 7:
		if(a>=0&&a<=3){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+700;
			printf("장비강화 성공 후전투력: %d\r\n",power);
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 8:
		if(a>=0&&a<=2){
			printf("강화성공\r\n");
			itemplus++;
			sprintf(buff,"%d",itemplus);
			write(fditemup,buff,sizeof(buff));
			printf("장비강화 성공 후 강화된 수:%d\r\n",itemplus);
			sleep(1);
			power=power+800;
			printf("장비강화 성공 후전투력: %d\r\n",power);;
			sprintf(buff,"%d",power);
	        write(fdpower,buff,sizeof(buff));
			break;
		}
		else{
			printf("강화실패\r\n");
			sleep(1);
			break;
		}
		
		case 9:
		printf("더 이상 강화할수 없습니다.\r\n");
		sleep(1);
		break;
}
	//printf("%d\n",a);
	close(fditemup);
	close(fdpower);
	return 0;

}
