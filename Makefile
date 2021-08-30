all: main

CXX  := g++
#CXXFLAGS = -std=c++11
OBJS := main.o macbinary.o
SRCS := $(patsubst %.o,%.cc,$(OBJS))

main: $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJS): Makefile macbinary.hh offsets.hh bigendian.hh resforkreader.hh

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o main
