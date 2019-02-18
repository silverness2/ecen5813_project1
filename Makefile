main: main.o
	gcc -o main main.o

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm -r *.o main
