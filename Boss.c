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
#include "../libfbdev/libfbdev.h"
#include "../libjpeg/jpeglib.h"

int Boss()
{
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
	int screen_width;
    int screen_height;
   	int bits_per_pixel;
   	int line_length;
   	int cols = 0, rows = 0;
	char *data;
	//FrameBuffer init
   	if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{		
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	
	int conFD = open ("/dev/tty0", O_RDWR);
	ioctl(conFD, KDSETMODE, KD_GRAPHICS);
	close (conFD);
		
	//Clear FB.
	fb_clear();
	
	//FileRead
	int error=0;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	
	
	fp = fopen("boss.jpg", "rb");
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE); 
	//printf ("JPG %d by %d by %d, %d\n",
	//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
	cols = cinfo.image_width;
	rows = cinfo.image_height;
		
	data = malloc(cols*rows*3);
	int currPoint = 0;
	jpeg_start_decompress(&cinfo);
	while(cinfo.output_scanline < cinfo.output_height) 
	{
		//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
		char *tempPtr=&data[currPoint];
		jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
		currPoint+=cols*3;
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);
	fb_write_reverse(data, cols,rows);
	free(data);

	fb_close();
	
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
		
		if(BossHP/300>=5&&BossHP/300<13){
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
		if(BossHP/300<5){
			buzzerInit();
			buzzerPlatSong(5);
			sleep(2);
			buzzerStopSong();
			//buzzerEnable(0);
		}
		else
		;
	}
										//FrameBuffer init
   										if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
										{		
											printf ("FrameBuffer Init Failed\r\n");
											return 0;
										}
	
										conFD = open ("/dev/tty0", O_RDWR);
										ioctl(conFD, KDSETMODE, KD_GRAPHICS);
										close (conFD);
		
										//Clear FB.
										fb_clear();
	
										//FileRead
										error=0;
										cinfo.err = jpeg_std_error(&jerr);
										jpeg_create_decompress(&cinfo);
	
	
										fp = fopen("test.jpg", "rb");
										jpeg_stdio_src(&cinfo, fp);
										jpeg_read_header(&cinfo, TRUE); 
										//printf ("JPG %d by %d by %d, %d\n",
										//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
										cols = cinfo.image_width;
										rows = cinfo.image_height;
																				
										data = malloc(cols*rows*3);
										currPoint = 0;
										jpeg_start_decompress(&cinfo);
										while(cinfo.output_scanline < cinfo.output_height) 
										{
											//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
											char *tempPtr=&data[currPoint];
											jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
											currPoint+=cols*3;
										}
										jpeg_finish_decompress(&cinfo);
										jpeg_destroy_decompress(&cinfo);
										fclose(fp);
										fb_write_reverse(data, cols,rows);
										free(data);

										fb_close();
	buzzerExit();
	ledLibExit();
	return 0;
}

