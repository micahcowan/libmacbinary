all: main

OBJS := main.o macbinary.o

main: $(OBJS) Makefile
	g++ -o $@ $(OBJS)

%.o: %.cc macbinary.hh Makefile
	g++ -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o main
