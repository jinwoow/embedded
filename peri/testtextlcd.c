#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h>
#include "textlcddrv.h"

int main(){
	printf("what\r\n");
	textlcd(1,'hello');
}
