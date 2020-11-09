#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"

int main()
{
	ledLibInit();
	ledOnOff(0,0);
	ledStatus();
	ledLibExit();
}
