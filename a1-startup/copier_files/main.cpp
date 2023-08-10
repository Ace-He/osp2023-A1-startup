/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/* global variables if needed go here */
int main(int argc, char** argv) {
    /* check command line arguments */
    if (argc != 3) {
        fprintf(stderr, "Please use this command: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }
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
    return EXIT_SUCCESS;
}
