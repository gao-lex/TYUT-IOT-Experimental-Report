ex4:main.o mytool1.o mytool2.o
	gcc main.o mytool1.o mytool2.o -o ex4
main.o:main.c
	gcc -c main.c
mytool1.o:mytool1.c
	gcc -c mytool1.c
mytool2.o:mytool2.c
	gcc -c mytool2.c
.PHONY:clean
clean:
	rm ex4 *.o