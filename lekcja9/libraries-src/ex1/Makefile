SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-Wall


main: $(OBJECTS)
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS) main

.PHONY: clean
