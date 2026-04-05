compiler = g++
flags = -std=c++17 -Wall
compile = $(compiler) $(flags) -c
link = $(compiler) $(flags) -o

my2CA.o: 2CA.cpp functionHeaders.h
	$(compile) $< -o $@

my2CA :my2CA.o
	$(link) $@ $^

test : my2CA
	./$<

clean:
	rm my2CA
	rm my2CA.o