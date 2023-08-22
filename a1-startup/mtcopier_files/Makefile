##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##
default:
	@echo "Please use 'make mtcopier' to compile the program."

mtcopier: main.o reader.o writer.o global_data.o
	g++ -Wall -Werror -std=c++20 -g -O -o $@ $^ -lpthread

%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $^

clean:
	rm -f mtcopier *.o *.dSYM




# provide make targets here to build the two programs 
