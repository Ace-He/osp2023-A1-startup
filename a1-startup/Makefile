##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##
default:
	@echo "Please use 'make copier', 'make mtcopier' or 'make all' to compile the program."

all: copier mtcopier

copier: copier_files/main.o copier_files/reader.o copier_files/writer.o
	g++ -Wall -Werror -std=c++20 -g -O -o $@ $^

mtcopier: mtcopier_files/main.o mtcopier_files/reader.o  mtcopier_files/writer.o  mtcopier_files/global_data.o
	g++ -Wall -Werror -std=c++20 -g -O -o $@ $^ -lpthread

mtcopier_files/%.o: mtcopier_files/%.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $< -o $@

copier_files/%.o: copier_files/%.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $< -o $@

clean:
	rm -f mtcopier copier mtcopier_files/*.o copier_files/*.o *.dSYM




# provide make targets here to build the two programs 
