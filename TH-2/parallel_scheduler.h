#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <pthread.h>

#include <cstddef>
#include <functional>

class parallel_scheduler
{
   private:
    size_t max_capacity_;
    pthread_t* thread_pool;

   public:
    parallel_scheduler(size_t max_capacity);
    ~parallel_scheduler();
    void run(std::function<void()> task);
};

#endif

