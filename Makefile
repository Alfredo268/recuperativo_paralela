CXX = mpic++
CXXFLAGS = -g3 -Wall
MKDIR = mkdir -p

LIBS=-lm -lmpi

directorios: 
	$(MKDIR) build dist

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o
	$(CXX) $(CXXFLAGS) -o programa build/main.o  $(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out programa  build

.DEFAULT_GOAL := all