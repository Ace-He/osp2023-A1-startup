//
// Created by Ace.He on 14/08/2023.
//
#include "global_data.h"

pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataAvailable = PTHREAD_COND_INITIALIZER;
pthread_cond_t spaceAvailable = PTHREAD_COND_INITIALIZER;
pthread_cond_t threadsDone = PTHREAD_COND_INITIALIZER;
const size_t MAX_QUEUE_SIZE = 50;

std::deque<std::string> shared_queue; // 共享队列
bool done_reading = false;  // 标记是否完成读取