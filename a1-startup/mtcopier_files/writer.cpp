/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

#include "global_data.h"


/**
 * implement these functions requred for the writer class
 **/
std::ofstream writer::out;

void writer::init(const std::string& name) {
    out.open(name);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
}

void writer::run() {
    pthread_create(&thread, nullptr, runner, nullptr);
}

void* writer::runner(void* arg) {
    while (true) {
        pthread_mutex_lock(&threadMutex);

        while (shared_queue.empty() && !done_reading) {
            pthread_cond_wait(&dataAvailable, &threadMutex);
        }

        if (shared_queue.empty() && done_reading) {
            // pthread_mutex_unlock(&threadMutex);
            break;
        }

        std::string line = shared_queue.front();
        shared_queue.pop_front();

        out << line << std::endl;

        //pthread_cond_signal(&spaceAvailable);

        pthread_mutex_unlock(&threadMutex);
        pthread_cond_signal(&spaceAvailable);
    }

    // 如果文件未关闭，则关闭文件
    // 这里已经完成了所有的写入，所以可以安全地关闭文件
    if (out.is_open()) {
        out.close();
    }

    //out.close();

    // 然后再释放锁
    pthread_mutex_unlock(&threadMutex);
    // 通知所有 reader 线程（如果有的话，没有的话也不会有问题，避免死锁）
    // 当然，这一步也可以放到 reader 的 run 方法中
    pthread_cond_broadcast(&spaceAvailable);

    return nullptr;
}

//void writer::append(const std::string& line) {
//    pthread_mutex_lock(&threadMutex);
//    while (shared_queue.size() >= MAX_QUEUE_SIZE) {
//        pthread_cond_wait(&spaceAvailable, &threadMutex);
//    }
//    shared_queue.push_back(line);
//    pthread_cond_signal(&dataAvailable);
//    pthread_mutex_unlock(&threadMutex);
//}

//void writer::setfinished() {
//    done_reading = true;
//    pthread_cond_broadcast(&dataAvailable);
//}

pthread_t writer::getThread() const{
    return thread;
}

writer::~writer() {
    if (out.is_open()) {
        out.close();
    }
}
