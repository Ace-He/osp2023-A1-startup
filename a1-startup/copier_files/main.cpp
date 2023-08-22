/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
#include <ctime>

/* global variables if needed go here */
int main(int argc, char** argv) {
    /* check command line arguments */
    bool timingEnabled = false;
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Please use this command: %s <input file> <output file> [-t]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // check -t flag
    if (argc == 4 && std::string(argv[3]) == "-t") {
        timingEnabled = true;
    }

    clock_t start = 0, end, duration;

    if (timingEnabled) start = clock();

    std::cout << "Single thread copy work start: " << std::endl;

    /* load the file and copy it to the destination */
    try {
        writer mywriter(argv[2]);
        reader myreader(argv[1], mywriter);
        myreader.run();
        mywriter.run();
    } catch (std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return EXIT_FAILURE;
    }

    if (timingEnabled) {
        end = clock();
        if (end != (clock_t)-1) {
            duration = end - start;
            double seconds = (double)duration / CLOCKS_PER_SEC;
            std::cout << "Time taken:  " << seconds << " seconds." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
