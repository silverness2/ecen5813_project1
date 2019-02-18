CFLAGS = -Wall -Werror

main: main.o
	gcc -o main main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

clean:
	rm -r *.o main
