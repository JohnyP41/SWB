# Main makefile

main: main.o dbgPrint.o
	g++ main.o dbgPrint.o -o main
main.o: main.cpp main.h
	g++ -c main.cpp
dbgPrint.o: dbgPrint.cpp dbgPrint.h
	g++ -c dbgPrint.cpp
clean:
	-rm -f *.o main
