#include <iostream>

#include "shared_array.h"

int main()
{
    shared_array shared_data("/test", 5);

    while (true)
    {
        shared_data.lock();
        for (int index = 0; index < 5; ++index)
        {
            std::cout << "Second Process: Reading " << shared_data[index] << " from index " << index << std::endl;
        }
        shared_data.unlock();
        sleep(1);
    }

    return 0;
}

