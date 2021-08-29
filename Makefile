all: main

CXX  := g++
CXXFLAGS = -std=c++11
OBJS := main.o macbinary.o ressectioniter.o

main: $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cc macbinary.hh Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o main
