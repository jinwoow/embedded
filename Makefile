main.elf:main.o good
	gcc main.o -l good -L. -o main.elf -lpthread

CFLAGS= -shared -fPIC

main.o:main.c myProject.h
	gcc -c -o main.o main.c

good:item.o power.o itemp.o itemup.o myProject.h
	gcc -o libgood.so -shared -fPIC item.o power.o itemp.o itemup.o

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

