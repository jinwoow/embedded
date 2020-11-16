#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <sys/stat.h>
#include <dirent.h>
#include "buzzer.h"

int main(void){
   buzzerInit();
   buzzerPlatSong(1);
   sleep(1);
   buzzerStopSong();
   buzzerExit();
}
