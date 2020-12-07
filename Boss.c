#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/kd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "accelMagGyro.h"
#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int Boss()
{
	buzzerInit();
	int fd = 0;
	FILE *fp = NULL;
	ledLibInit();
	int fdpower;
	char buf[1024];
	off_t newpos;
	ssize_t nread;
	int cnt=0;
	char buff[6];
	int BossHP=30000;
	
	//Accelerometer
	fd = open (ACCELPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (ACCELPATH "data", "rt");
	int accel[3];
	fscanf(fp,"%d, %d, %d",&accel[0],&accel[1],&accel[2]);
	printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
	fclose(fp);

	//Magnet
	fd = open (MAGNEPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (MAGNEPATH "data", "rt");
	int magne[3];
	fscanf(fp,"%d, %d, %d",&magne[0],&magne[1],&magne[2]);
	printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
	fclose(fp);

	//Gyroscope
	fd = open (GYROPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (GYROPATH "data", "rt");
	int gyro[3];
	fscanf(fp,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);
	printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
	fclose(fp);
	
	//보스 피 에서 - 내 전투력을 빼면 된다
	//BossHP=30000;
	ledOnOff0(0,1);
	textlcd("1","BOSS!!!!");
	fdpower=open("power.txt",O_RDONLY);
	if(fdpower==-1){
		printf("fdpower file open error!\n");
		exit(1);
	}
	printf("보스 입장시 전투력 : ");
	while(nread=read(fdpower,buf,1024)>0){
		printf("%s\r\n",buf);
		lseek(fdpower,(off_t)0,SEEK_CUR);
	}
	int power=atoi(buf);
	close(fdpower);
	printf("power:%d",power);
	sleep(1);
	
	while(BossHP>0){
		sleep(1);
		BossHP=BossHP-power;
		
		if(accel[0]<-20000){
			printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
			power=power+10;
		}
		if(accel[1]>500){
			printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
			power=power+10;
		}
		if(accel[2]>500){
			printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
			power=power+10;
		}
		if(magne[0]>-1000){
			printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
			power=power+10;
		}
		if(magne[1]>1000){
			printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
			power=power+10;
		}
		if(magne[1]>3000){
			printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
			power=power+10;
		}
		if(gyro[0]>10)
		{
			printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
			power=power+10;
		}
		if(gyro[1]>10)
		{
			printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
			power=power+10;
		}
		if(gyro[2]>10)
		{
			printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
			power=power+10;
		}
		
		

		printf("보스 체력: %d\n",BossHP);
		
		if(BossHP/300>=0&&BossHP/300<13){
			ledOnOff8(0,1);
			textlcd("2","Hp : 10%");
		}
		else if(BossHP/300>=13&&BossHP/300<26){
			ledOnOff7(0,1);
			textlcd("2","Hp : 20%");
		}
		else if(BossHP/300>=26&&BossHP/300<39){
			ledOnOff6(0,1);
			textlcd("2","Hp : 30%");
		}
		else if(BossHP/300>=39&&BossHP/300<52){
			ledOnOff5(0,1);
			textlcd("2","Hp : 40%");
		}
		else if(BossHP/300>=52&&BossHP/300<65){
			ledOnOff4(0,1);
			textlcd("2","Hp : 50%");
		}
		else if(BossHP/300>=65&&BossHP/300<78){
			ledOnOff3(0,1);
			textlcd("2","Hp : 60%");
		}
		else if(BossHP/300>=78&&BossHP/300<91){
			ledOnOff2(0,1);
			textlcd("2","Hp : 70%");
		}
		else if(BossHP/300>=91&&BossHP/300<100){
			ledOnOff1(0,1);
			textlcd("2","BOSS ATTACK ");
		}
		if(BossHP/300<=0){
			buzzerPlatSong(5);
			sleep(2);
			buzzerStopSong();
			buzzerExit();
		}
		else
		;
	}
	buzzerExit();
	ledLibExit();
	return 0;
}

