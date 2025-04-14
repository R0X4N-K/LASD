CC=g++
CFLAGS= -c -Wall
all: final
final: main.o functions.o
	$(CC) main.o functions.o -O3 -o final
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
functions.o: functions.cpp
	$(CC) $(CFLAGS) functions.cpp
clean:
	rm -rf *.o
	rm -rf final
