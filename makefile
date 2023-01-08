CC=clang
CFLAGS=-Wall -g3 -std=c17 -pedantic
LDFLAGS=
EXEC=main

all: $(EXEC) clean

errs.o: ./utils/args/errs.c
	$(CC) -c ./utils/args/errs.c $(CFLAGS)

list.o: ./utils/list/list.c errs.o
	$(CC) -c ./utils/list/list.c errs.o $(CFLAGS)

math.o: ./utils/math/math.c list.o errs.o
	$(CC) -c ./utils/math/math.c list.o errs.o $(CFLAGS)

draw.o: ./utils/graphic/draw.c math.o list.o errs.o
	$(CC) -c ./utils/graphic/draw.c math.o list.o errs.o $(CFLAGS)

graphic.o: ./utils/graphic/graphic.c draw.o math.o list.o errs.o
	$(CC) -c ./utils/graphic/graphic.c draw.o math.o list.o errs.o $(CFLAGS)

enveloppe.o: ./utils/graphic/enveloppe.c graphic.o draw.o math.o list.o errs.o
	$(CC) -c ./utils/graphic/enveloppe.c graphic.o draw.o math.o list.o errs.o $(CFLAGS)

inception.o: ./utils/graphic/inception.c enveloppe.o graphic.o draw.o math.o list.o errs.o
	$(CC) -c ./utils/graphic/inception.c enveloppe.o graphic.o draw.o math.o list.o errs.o $(CFLAGS)

main.o: main.c errs.o list.o math.o draw.o graphic.o enveloppe.o inception.o
	$(CC) -c main.c errs.o list.o math.o draw.o graphic.o enveloppe.o inception.o $(CFLAGS) -lMLV -lm

main: main.o errs.o list.o math.o draw.o graphic.o enveloppe.o inception.o
	$(CC) -o main main.c errs.o list.o math.o draw.o graphic.o enveloppe.o inception.o $(CFLAGS) -lMLV -lm

clean:
	rm -f *.o *~ 

mrproper: clean
	rm -rf $(EXEC)

default: clean