# Main makefile
CC=g++
CFLAGS=-c -Wall

heapproject: heapproject.o heap.o infoelement.o 
	$(CC) -pg -g $^ -o $@

%.o: %.cpp %.h
	$(CC) -pg -g $(CFLAGS) $< -o $@


clean:
	rm -f ./*.o heapproject
