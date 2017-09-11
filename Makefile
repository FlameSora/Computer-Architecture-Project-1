CC=gcc

default: runfile

runfile.o: main.c 
	gcc -c main.c -o runfile.o 
 
runfile: runfile.o
	$(CC) runfile.o  -o runfile

clean:
	rm -f *.o
	rm -f runfile
