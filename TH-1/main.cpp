#include <pthread.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

struct Data
{
    const std::vector<int>* data_array;
    std::size_t start_index;
    std::size_t end_index;
    long long partial_sum;
};

void* compute_partial_sum(void* arg)
{
    Data* thread_data = static_cast<Data*>(arg);
    thread_data->partial_sum = std::accumulate(thread_data->data_array->begin() + thread_data->start_index, 
                                                thread_data->data_array->begin() + thread_data->end_index, 0LL);
    return nullptr;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <array_size> <thread_count>" << std::endl;
        return 1;
    }

    std::size_t array_size = std::stoull(argv[1]);
    int thread_count = std::stoi(argv[2]);

    std::vector<int> data_array(array_size);
    for (auto& element : data_array)
    {
        element = rand() % 100;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    long long single_thread_result = std::accumulate(data_array.begin(), data_array.end(), 0LL);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> single_thread_duration = end_time - start_time;
    std::cout << "Time spent without threads: " << single_thread_duration.count() << " seconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::vector<pthread_t> thread_ids(thread_count);
    std::vector<Data> thread_data(thread_count);
    std::size_t segment_size = array_size / thread_count;

    for (int i = 0; i < thread_count; ++i)
    {
        thread_data[i] = {&data_array, i * segment_size, (i == thread_count - 1) ? array_size : (i + 1) * segment_size, 0};
        pthread_create(&thread_ids[i], nullptr, compute_partial_sum, &thread_data[i]);
    }

    for (int i = 0; i < thread_count; ++i)
    {
        pthread_join(thread_ids[i], nullptr);
    }

    long long multi_thread_result = 0;
    for (const auto& data : thread_data)
    {
        multi_thread_result += data.partial_sum;
    }

    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> multi_thread_duration = end_time - start_time;
    std::cout << "Time spent with " << thread_count << " threads: " << multi_thread_duration.count() << " seconds" << std::endl;

    return 0;
}

