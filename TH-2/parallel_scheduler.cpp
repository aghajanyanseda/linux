#include "parallel_scheduler.h"

#include <unistd.h>

#include <queue>

std::queue<std::function<void()>> task_queue;
pthread_cond_t condition_var;
pthread_mutex_t mutex_lock;
bool is_stopped = false;

void* worker_thread(void* arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex_lock);
        while (task_queue.empty() && !is_stopped) pthread_cond_wait(&condition_var, &mutex_lock);
        if (task_queue.empty() && is_stopped)
        {
            pthread_mutex_unlock(&mutex_lock);
            break;
        }
        auto current_task = task_queue.front();
        task_queue.pop();
        pthread_mutex_unlock(&mutex_lock);
        current_task();
    }
    return nullptr;
}

parallel_scheduler::parallel_scheduler(size_t max_capacity) : max_capacity_(max_capacity)
{
    pthread_mutex_init(&mutex_lock, nullptr);
    pthread_cond_init(&condition_var, nullptr);
    thread_pool = new pthread_t[max_capacity_];
    for (size_t i = 0; i < max_capacity_; ++i) pthread_create(&thread_pool[i], nullptr, worker_thread, nullptr);
}

parallel_scheduler::~parallel_scheduler()
{
    pthread_mutex_lock(&mutex_lock);
    is_stopped = true;
    pthread_cond_broadcast(&condition_var);
    pthread_mutex_unlock(&mutex_lock);
    for (size_t i = 0; i < max_capacity_; ++i) pthread_join(thread_pool[i], nullptr);
    pthread_cond_destroy(&condition_var);
    pthread_mutex_destroy(&mutex_lock);
    delete[] thread_pool;
}

void parallel_scheduler::run(std::function<void()> task)
{
    pthread_mutex_lock(&mutex_lock);
    task_queue.push(task);
    pthread_cond_signal(&condition_var);
    pthread_mutex_unlock(&mutex_lock);
}

