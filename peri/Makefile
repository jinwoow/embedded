all: libMyperi.a

libMyperi.a:button.o led.o buzzer.o textlcd.o fnd.o colorled.o Temperature.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o buzzer.o textlcd.o fnd.o colorled.o Temperature.o

button.o:button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

led.o:led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

buzzer.o:buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

textlcd.o:TextLCD.c textlcddrv.h
	arm-linux-gnueabi-gcc -c TextLCD.c -o textlcd.o

fnd.o:fnd.c fnddrv.h
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

colorled.o:colarled.c
	arm-linux-gnueabi-gcc -c colarled.c -o colorled.o

Temperature.o:Temperature.c
	arm-linux-gnueabi-gcc -c Temperature.c -o Temperature.o

clean:
	rm *.o
	rm *.a
