all: libMyperi.a

libMyperi.a:button.o led.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o

button.o:button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

led.o:led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

clean:
	rm *.o
	rm *.a
