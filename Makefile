CC = gcc
CFLAGS = -Wall -g

all: server

server: main.o echo.o
	$(CC) $(CFLAGS) -o server main.o echo.o

main.o: main.c echo.h
	$(CC) $(CFLAGS) -c main.c

echo.o: echo.c echo.h
	$(CC) $(CFLAGS) -c echo.c

clean:
	rm -f *.o server