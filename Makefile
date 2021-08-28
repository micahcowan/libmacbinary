all: main

main: main.o Makefile
	g++ -o $@ $<

%.o: %.cc macbinary.hh Makefile
	g++ -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o main
