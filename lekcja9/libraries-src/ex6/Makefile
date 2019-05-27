CXXFLAGS += -std=c++11 -g
OBJECTS = linker.o ElfRelocObject.o ElfExecutable.o

linker: $(OBJECTS)
	g++ $(CXXFLAGS) $(OBJECTS) -o $@

linker.o: linker.cpp
	g++ $(CXXFLAGS) $< -c -o $@

ElfRelocObject.o: ElfRelocObject.cpp
	g++ $(CXXFLAGS) $< -c -o $@

ElfExecutable.o: ElfExecutable.cpp
	g++ $(CXXFLAGS) $< -c -o $@

clean:
	rm -f *.o linker
