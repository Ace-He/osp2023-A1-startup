/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include "global_data.h"
#include <cstdlib>
#include <vector>

/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;

using namespace std;

void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    if (readers) {
        delete[] readers;
        readers = nullptr;
    }
    if (writers) {
        delete[] writers;
        writers = nullptr;
    }

    pthread_mutex_destroy(&threadMutex);
    pthread_cond_destroy(&dataAvailable);
    pthread_cond_destroy(&spaceAvailable);
}

int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/
    bool timingEnabled = false;
    // 检查命令行参数
    if (argc < 4 || argc > 5) {
        std::cerr << "Usage: " << argv[0] << " number_of_threads infile outfile [-t]" << std::endl;
        return EXIT_FAILURE;
    }

    /**
     * process command line arguments
     **/
    int numThreads = std::stoi(argv[1]);
    if(numThreads < 25 || numThreads > 100) {
         fprintf(stderr, "Number of threads should be between 25 and 100.\n");
         return EXIT_FAILURE;
    }

    // check -t flag
    if (argc == 5 && std::string(argv[4]) == "-t") {
        timingEnabled = true;
    }

    clock_t start = 0, end, duration;

    // Initialize the global mutex and condition variables
    pthread_mutex_init(&threadMutex, nullptr);
    pthread_cond_init(&dataAvailable, nullptr);
    pthread_cond_init(&spaceAvailable, nullptr);

    std::vector<pthread_t> threads;

    /**
     * initialize the reader and writer classes
     **/
    if (timingEnabled) start = clock();
    std::cout << "mt copier work start: " << std::endl;

    readers = new reader[numThreads];
    writers = new writer[numThreads];

    reader::init(argv[2]);
    writer::init(argv[3]);

    /**
     * initialize the running of each thread. Note you just call run() on each
     * object here, you'll call pthread_create itself in the run function.
     **/
    for (int i = 0; i < numThreads; i++) {
        readers[i].run();  // 保存线程ID
        writers[i].run();  // 保存线程ID
    }

    /**
     *
     * have loop here waiting for the threads to complete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    for (int i = 0; i < numThreads; i++) {
        pthread_join(readers[i].getThread(), nullptr);
        pthread_join(writers[i].getThread(), nullptr);
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


