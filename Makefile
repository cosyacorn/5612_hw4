CC=gcc
CFLAGS=-Wall -lreadline

objects=main.o

main: $(objects)
	$(CC) -o shell $(objects) $(CFLAGS)

clean:
	$(RM) shell $(objects)
