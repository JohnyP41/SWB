CC=gcc

main: main.o libauth.so
	$(CC) main.o -Wl,-rpath=. -L. -lauth -o main

auth.o: auth.c
	$(CC) -c auth.c -o auth.o -fPIC

libauth.so: auth.o
	ld auth.o -shared -o libauth.so

main.o: main.c
	$(CC) -c main.c -o main.o

clean:
	rm -f auth.o main.o libauth.so main    libcheat.so cheat.o

cheat.o: cheat.c
	gcc -c cheat.c -o cheat.o -fPIC

libcheat.so: cheat.o
	ld cheat.o -shared -o libcheat.so

cheat: libcheat.so

.PHONY: clean cheat
