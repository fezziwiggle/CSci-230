all: hw5-MaezyHaldeman.o hw5-A-MaezyHaldeman.o hw5-B-MaezyHaldeman.o hw5-C-MaezyHaldeman.o hw5-D-MaezyHaldeman.o
	gcc hw5-MaezyHaldeman.o hw5-A-MaezyHaldeman.o hw5-B-MaezyHaldeman.o hw5-C-MaezyHaldeman.o hw5-D-MaezyHaldeman.o -o myProg

hw5-MaezyHaldeman.o: hw5-MaezyHaldeman.c
	gcc -c hw5-MaezyHaldeman.c

hw5-A-MaezyHaldeman.o: hw5-A-MaezyHaldeman.c
	gcc -c hw5-A-MaezyHaldeman.c

hw5-B-MaezyHaldeman.o: hw5-B-MaezyHaldeman.c
	gcc -c hw5-B-MaezyHaldeman.c

hw5-C-MaezyHaldeman.o: hw5-C-MaezyHaldeman.c
	gcc -c hw5-C-MaezyHaldeman.c

hw5-D-MaezyHaldeman.o: hw5-D-MaezyHaldeman.c
	gcc -c hw5-D-MaezyHaldeman.c

clean:
	rm -rf *.o myProg
