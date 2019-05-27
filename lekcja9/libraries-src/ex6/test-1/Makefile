.PHONY: test doexit

test: doexit check.sh
	./check.sh

doexit: ../linker exit.o doexit.o
	../linker exit.o doexit.o $@

exit.o: exit.s
	as $< -o $@

doexit.o: doexit.c
	gcc $< -c -o $@

clean:
	rm -rf exit.o doexit.o doexit
