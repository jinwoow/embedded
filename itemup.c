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
	
	
	FILE *fp = fopen("upgrade.jpg", "rb");
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
	textlcd("2","i can do it");
	textlcd("1","upgrade..wait 4");
	sleep(1);
	textlcd("1","upgrade..wait 3");
	sleep(1);
	textlcd("1","upgrade..wait 2");
	sleep(1);
	textlcd("1","upgrade..wait 1");
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
	//msgRx.keyInput=0;
	//returnValue=0;
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
															sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
															sleep(2);
														break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
															sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
	 												       sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
	   												     sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
	  												      sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
	     												   sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
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
	    												    sleep(2);
															break;
														}
														else{
															textlcd("1","fail");
															sleep(2);
															break;
														}
		
														case 9:
															textlcd("1","Don't be greedy.");
															printf("더 이상 강화할수 없습니다.\r\n");
															sleep(2);
															break;
														}
														
	close(fditemup);
	close(fdpower);
	return 0;

}
