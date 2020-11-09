#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"

int main()
{
	ledLibInit();
	ledStatus();
	sleep(2);
	ledLibExit();
}
