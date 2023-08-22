/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <functional>



reader::reader(const std::string& name, writer& mywriter) : thewriter(mywriter) {
    in.open(name);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }
}


void reader::run() {
    std::string line;
    while (std::getline(in, line)) {
        thewriter.append(line);
    }
    in.close();
}
