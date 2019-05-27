.PHONY: test doexit

test: doexit check.sh
	./check.sh

doexit: ../linker doexit.o
	../linker doexit.o $@

doexit.o: doexit.c
	gcc $< -c -o $@

clean:
	rm -rf doexit.o doexit
