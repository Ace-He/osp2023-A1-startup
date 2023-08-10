##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##
.default: all

all: copier

clean:
	rm -f copier *.o *.dSYM

copier: main.o reader.o writer.o
	g++ -Wall -Werror -std=c++20 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $^




# provide make targets here to build the two programs 
