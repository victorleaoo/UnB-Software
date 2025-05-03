CC=gcc
CFLAGS=-fopenmp -Wall -Wextra

OBJSUM := $(patsubst %.c,%.o,$(wildcard src/*.c))
OBJSUMF := $(patsubst %.c,%.exec,$(wildcard src/*.c))

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: main.o vsum
	@echo "Compiled!"

%.exec: %.o
	$(CC) $(CFLAGS) -o $@ $< main.o

vsum: $(OBJSUMF)

clean:
	rm -rf main.o src/*.exec $(OBJSUM) $(OBJSUMF)
