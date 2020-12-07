CC :=arm-linux-gnueabi-gcc

all: main.elf

main.elf:main.o libMyperi.a
	mv libMyperi.a ../
	$(CC) main.o -o main.elf -L../ -L../libjpeg -l mylib -l jpeg -l Myperi -lpthread

	
main.o:main.c button.h
	$(CC) -c -o main.o main.c

libMyperi.a:item.o power.o itemp.o itemup.o Boss.o button.o led.o buzzer.o textlcd.o fnd.o colorled.o Temperature.o accelMagGyro.o
	arm-linux-gnueabi-ar rc libMyperi.a item.o power.o itemp.o itemup.o button.o led.o buzzer.o textlcd.o fnd.o colorled.o Temperature.o accelMagGyro.o Boss.o

item.o:readitem.c 
	$(CC) -c readitem.c -o item.o

Boss.o:Boss.c accelMagGyro.o Temperature.o led.o textlcd.o buzzer.o
	$(CC) -c Boss.c -o Boss.o
	
power.o:readpower.c fnd.o Temperature.o
	$(CC) -c readpower.c -o power.o 

itemp.o:readitemp.c
	$(CC) -c readitemp.c -o itemp.o
	
itemup.o:itemup.c textlcd.o button.o led.o textlcd.o colorled.o fnd.o button.h
	$(CC) -c itemup.c -o itemup.o

button.o:button.h button.c
	$(CC) -c button.c -o button.o

led.o:led.h led.c
	$(CC) -c led.c -o led.o

buzzer.o:buzzer.h buzzer.c
	$(CC) -c buzzer.c -o buzzer.o

textlcd.o:TextLCD.c textlcddrv.h
	$(CC) -c TextLCD.c -o textlcd.o

fnd.o:fnd.c fnddrv.h
	$(CC) -c fnd.c -o fnd.o

colorled.o:colarled.c
	$(CC) -c colarled.c -o colorled.o

Temperature.o:Temperature.c power.o
	$(CC) -c Temperature.c -o Temperature.o

accelMagGyro.o:accelMagGyro.h accelMagGyro.c
	$(CC) -c accelMagGyro.c -o accelMagGyro.o

	
clean:
	rm -f *.o
	rm -f *.so
	rm -f *.elf


