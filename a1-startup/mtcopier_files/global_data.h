//
// Created by Ace.He on 14/08/2023.
//

#ifndef OSP2023_A1_STARTUP_GLOBAL_DATA_H
#define OSP2023_A1_STARTUP_GLOBAL_DATA_H

#include <pthread.h>
#include <deque>
#include <string>

extern pthread_mutex_t threadMutex;
extern pthread_cond_t dataAvailable;   // 数据可用条件变量
extern pthread_cond_t spaceAvailable;  // 队列中有空间的条件变量
extern pthread_cond_t threadsDone;

extern int finishedThreadsCount;  // 已完成的线程数
extern const size_t MAX_QUEUE_SIZE;
extern std::deque<std::string> shared_queue;
extern bool done_reading;  // 标记是否完成读取

#endif //OSP2023_A1_STARTUP_GLOBAL_DATA_H
