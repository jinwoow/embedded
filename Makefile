main.elf:main.o good
	gcc main.o -l good -L. -o main.elf -lpthread

CFLAGS= -shared -fPIC

main.o:main.c myProject.h
	gcc -c -o main.o main.c

good:1.o 2.o item.o power.o itemp.o itemup.o myProject.h
	gcc -o libgood.so -shared -fPIC 1.o 2.o item.o power.o itemp.o itemup.o

1.o:1.c myProject.h
	gcc -o 1.o $(CFLAGS) -c 1.c

2.o:2.c myProject.h
	gcc -o 2.o $(CFLAGS) -c 2.c

item.o:readitem.c myProject.h
	gcc -o item.o $(CFLAGS) -c readitem.c

power.o:readpower.c myProject.h
	gcc -o power.o $(CFLAGS) -c readpower.c

itemp.o:readitemp.c myProject.h
	gcc -o itemp.o $(CFLAGS) -c readitemp.c

itemup.o:itemup.c myProject.h
	gcc -o itemup.o $(CFLAGS) -c itemup.c

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.elf

