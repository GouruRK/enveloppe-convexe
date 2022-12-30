CC=clang
CFLAGS=-Wall -W -g3 -std=c17
LDFLAGS=
EXEC=main

all: $(EXEC) clean

main: main.o list.o math.o
	$(CC) -o main main.o list.o math.o $(CFLAGS) -lMLV

main.o: main.c list.o math.o
	$(CC) -c main.c list.o math.o $(CFLAGS)

math.o: ./utils/math/math.c list.o
	$(CC) -c ./utils/math/math.c list.o $(CFLAGS)

list.o: ./utils/list/list.c
	$(CC) -c ./utils/list/list.c $(CFLAGS)

clean:
	rm -f *.o *~ 

mrproper: clean
	rm -rf $(EXEC)

default: clean