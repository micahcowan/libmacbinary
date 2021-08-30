all: main

CXX  := g++
CXXFLAGS = -std=c++11
OBJS := main.o macbinary.o

main: $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cc macbinary.hh restypelistiter.hh offsets.hh bigendian.hh resforkreader.hh restypeentry.h Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o main
