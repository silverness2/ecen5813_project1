CFLAGS = -Wall -Werror

main: main.o mem_manip.o
	gcc -o main main.o mem_manip.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

mem_manip.o: mem_manip.c
	gcc $(CFLAGS) -c mem_manip.c -o mem_manip.o

clean:
	rm -r *.o main
