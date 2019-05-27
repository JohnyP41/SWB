.PHONY: test doexit

test: doexit check.sh
	./check.sh

doexit: exit.o doexit.o storage.o ../linker
	../linker exit.o doexit.o storage.o $@

exit.o: exit.s
	as $< -o $@

doexit.o: doexit.c
	gcc $< -c -o $@

storage.o: storage.c
	gcc $< -c -o $@

clean:
	rm -rf exit.o doexit.o doexit storage.o
