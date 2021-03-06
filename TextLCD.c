#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include "textlcddrv.h"
#define TEXTLCD_DRIVER_NAME "/dev/peritextlcd"

int textlcd(char *line, char *text)
{
	printf("%s %s\r\n",line,text);
	unsigned int linenum = 0;
	stTextLCD stlcd; // stTextLCD 구조체를 가지고 드라이버와 인터페이스
	int fd;
	int len;
	memset(&stlcd,0,sizeof(stTextLCD)); // 구조체 초기화
	linenum = strtol(line,NULL,10);
	printf("linenum :%d\n", linenum);
	if ( linenum == 1)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	else if ( linenum == 2)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	else {
		printf("linenum : %d wrong . range (1 ~ 2)\n", linenum);
		return 1;
	}
	len = strlen(text);
	if ( len > COLUMN_NUM)
		memcpy(stlcd.TextData[stlcd.cmdData - 1], text, COLUMN_NUM);
	else
		memcpy(stlcd.TextData[stlcd.cmdData - 1], text, len);
	stlcd.cmd = CMD_WRITE_STRING;
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR); // open driver
	if ( fd < 0 ) {
	perror("driver (//dev//peritextlcd) open error.\n");
	return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	close(fd);
	return 0;
}

