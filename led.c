#include "led.h"
#include <fcntl.h>
#include <stdio.h>
static unsigned int ledValue=0;
static int fd=0;

int ledOnOff(int ledNum, int onOff)
{
	int i=1;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff0(int ledNum, int onOff)
{
	int i=1;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff1(int ledNum, int onOff)
{
	int i=1;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff2(int ledNum, int onOff)
{
	int i=2;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff3(int ledNum, int onOff)
{
	int i=4;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff4(int ledNum, int onOff)
{
	int i=8;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff5(int ledNum, int onOff)
{
	int i=16;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff6(int ledNum, int onOff)
{
	int i=32;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff7(int ledNum, int onOff)
{
	int i=64;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledOnOff8(int ledNum, int onOff)
{
	int i=128;
	i = i<<ledNum;
	ledValue=ledValue&(~i);
	if(onOff !=0)ledValue|=i;
	write(fd,&ledValue,4);
}

int ledStatus(void){
	ledOnOff(6,1);
}

int ledLibInit(void){
	fd=open("/dev/periled",O_WRONLY);
	ledValue=0;
}

int ledLibExit(void){
ledValue = 0;
ledOnOff (0, 0);
close(fd);
}
