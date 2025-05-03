CC=gcc
CFLAGS=-fopenmp -Wall -Wextra

all: 1-hello.exec
	@echo "Compiled!"

%.exec: %.o
	$(CC) -o $@ $+ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *.exec
