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
#include "../libfbdev/libfbdev.h"
#include "../libjpeg/jpeglib.h"
#include <linux/input.h>
#include <sys/stat.h>
#include "button.h"
#define MESSAGE_ID 1122
static int returnValue =0;


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
	

	textlcd("1","1. item upgrade");
	textlcd("2","2.exit");
	//lseek(fdpower,(off_t)0,SEEK_SET);
	textlcd("1","1. item upgrade");
	textlcd("2","2.exit");
	//printf("1: 장비강화\r\n");
	//printf("2: 종료\r\n");
    while(1){
		BUTTON_MSG_T msgRx;
		int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);//메시지큐
		while(1)
		{
			buttonInit();
			/*int screen_width;
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
			FILE *fp = fopen("test.jpg", "rb");
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

			fb_close();*/

			//printf("무엇을 선택하겠는가? ");

			returnValue=msgrcv(msgID,&msgRx,8,0,IPC_NOWAIT);
			if(returnValue>0)
			{
				if((msgRx.keyInput>0)&&(msgRx.pressed>0)){
					switch(msgRx.keyInput)
					{
						
						case KEY_VOLUMEUP:
										break;
						case KEY_HOME: 
										/*textlcd("1","bye");
										while(nread=read(fdpower,buf,1024)>0){
										printf("%s\r\n",buf);
										lseek(fdpower,(off_t)0,SEEK_CUR);
										}
										exit(1);*/
										break;
						case KEY_SEARCH: printf("Search key:"); break;
						case KEY_BACK: printf("Back key:"); break;
						case KEY_MENU: printf("Menu key:"); break;
						case KEY_VOLUMEDOWN:
											//FrameBuffer init
 									   /*if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
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

										fb_close();*/
										textlcd("1","input");
										textlcd("2","item upgrade");
										sleep(1);
										itemup();
										msgRx.keyInput=0;
										returnValue=0;break;
					}
					if(msgRx.pressed)
					printf("pressed\n\r");
				}
				else
				{
					printf("relesed\n");
					msgRx.keyInput=0;
					returnValue=0;
				}
		
			}
			else
			;
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

