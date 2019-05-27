all: add.o mul.o main.o

add.o: add.c
	gcc -c $< -o $@

mul.o: mul.c
	gcc -c $< -o $@

main.o: main.c
	gcc -c $< -o $@

clean:
	rm -f add.o mul.o main.o
