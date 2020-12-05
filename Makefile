all: accelMagGyro.h accelMagGyro.c
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyPeri.a accelMagGyro.o

