#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h>

int main(){
	colarled("10","10","10");
	sleep(3);
	colarled("90","90","90");
}
