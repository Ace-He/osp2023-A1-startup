##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##
default:
	@echo "Please use 'make copier' to compile the program."

copier: main.o reader.o writer.o
	g++ -Wall -Werror -std=c++20 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $^

clean:
	rm -f copier *.o *.dSYM




# provide make targets here to build the two programs 
