CFLAGS = -Wall -Werror

test: main testscript
	./main < testscript

main: main.o timer.o ui.o prng.o mem_manip.o
	gcc -o main main.o timer.o ui.o prng.o mem_manip.o

main.o: main.c ui.h mem_manip.h timer.h macro.h
	gcc $(CFLAGS) -c main.c -o main.o

mem_manip.o: mem_manip.c mem_manip.h macro.h
	gcc $(CFLAGS) -c mem_manip.c -o mem_manip.o

prng.o: prng.c prng.h
	gcc $(CFLAGS) -c prng.c -o prng.o

ui.o: ui.c ui.h macro.h
	gcc $(CFLAGS) -c ui.c -o ui.o

timer.o: timer.c timer.h macro.h
	gcc $(CFLAGS) -c timer.c -o timer.o

clean:
	rm -r *.o main
