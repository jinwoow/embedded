main.elf:main.o good
	gcc main.o -l good -L. -o main.elf

CFLAGS= -shared -fPIC

main.o:main.c myProject.h
	gcc -c -o main.o main.c


good:1.o 2.o myProject.h
	gcc -o libgood.so -shared -fPIC 1.o 2.o

1.o:1.c myProject.h
	gcc -o 1.o $(CFLAGS) -c 1.c

2.o:2.c myProject.h
	gcc -o 2.o $(CFLAGS) -c 2.c

clean:
	rm -f *.o
