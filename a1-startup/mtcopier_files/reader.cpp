/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"

#include "writer.h"

#include "global_data.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;

void reader::init(const std::string& name) {
    in.open(name);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }
}

void reader::run() {
    pthread_create(&thread, nullptr, runner, nullptr);
}


void* reader::runner(void* arg) {
    std::string line;

    while (true) {
        // Lock the mutex to safely access shared resources
        pthread_mutex_lock(&threadMutex);

        // Wait if the queue is full
        while (shared_queue.size() >= MAX_QUEUE_SIZE && !done_reading) {
            pthread_cond_wait(&spaceAvailable, &threadMutex);
        }

//        if (in.eof()) {
//            pthread_mutex_unlock(&mutex);
//            break;
//        }
//
//        // Read from the file
//        if (std::getline(in, line)) {
//            shared_queue.push_back(line);
//            pthread_cond_signal(&dataAvailable);  // Notify writer that data is available
//        }
//
//        pthread_mutex_unlock(&mutex);


        // Read from the file
        if (!done_reading && std::getline(in, line)) {
            shared_queue.push_back(line);
            pthread_mutex_unlock(&threadMutex);
            pthread_cond_signal(&dataAvailable);  // Notify writer that data is available
        } else {
            break;
        }

    }

//    done_reading = true;
//    pthread_cond_broadcast(&dataAvailable); // 通知所有线程
//    in.close();
// done_reading 也是共享资源，需要加锁
    if (!done_reading) {
        done_reading = true;
        // 可以完成后直接关闭文件
        in.close();
    }
    // 再释放锁（注意，更好的做法是先释放锁，再通知所有线程）
    pthread_mutex_unlock(&threadMutex);
    // 然后通知所有线程
    pthread_cond_broadcast(&dataAvailable); // 通知所有线程

    return nullptr;
}

pthread_t reader :: getThread() const {
    return thread;
}

reader::~reader() {
    if (in.is_open()) {
        in.close();
    }
}


