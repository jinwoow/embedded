#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

int main(){
   buzzerInit();
   buzzerPlaySong(1);
   buzzerStopSong();
   buzzerExit();
}
