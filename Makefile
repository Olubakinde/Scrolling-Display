# Makefile

INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm

all: scroll

scroll: main.o display.o input.o
        $(CC) -o scroll main.o display.o input.o $(LDFLAGS)

run: scroll
        ./scroll

clean:
        rm -f *.o scroll

main.o: main.c scroll.h
        $(CC) -c main.c $(INCLUDE)

display.o: display.c scroll.h
        $(CC) -c display.c $(INCLUDE)

input.o: input.c scroll.h
        $(CC) -c input.c $(INCLUDE)
