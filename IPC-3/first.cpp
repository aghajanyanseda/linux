#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int calculateNthPrime(int nth)
{
    std::vector<int> primes;
    int number = 2;

    while (primes.size() < nth)
    {
        bool is_prime = true;

        for (int prime : primes)
        {
            if (number % prime == 0)
            {
                is_prime = false;
                break;
            }
        }

        if (is_prime)
        {
            primes.push_back(number);
        }

        ++number;
    }

    return primes[nth - 1];
}

bool isValidNumber(const std::string &str)
{
    for (char const &ch : str)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}

void primeNumberCalculator()
{
    int pipe1[2];
    int pipe2[2];
    pid_t child_pid;

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
    {
        std::cout << "pipe() error" << std::endl;
        exit(errno);
    }

    child_pid = fork();
    if (child_pid < 0)
    {
        std::cout << "fork() error" << std::endl;
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        exit(errno);
    }
    else if (child_pid == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        char buffer[20];
        memset(buffer, 0, sizeof(buffer));

        read(pipe1[0], buffer, sizeof(buffer));

        if (std::string(buffer) == "exit")
        {
            close(pipe1[0]);
            close(pipe2[1]);
            exit(0);
        }

        if (std::string(buffer) == "invalid")
        {
            close(pipe1[0]);
            close(pipe2[1]);
            exit(0);
        }

        int num = atoi(buffer);
        std::cout << "[Child] Calculating the " << num << "-th prime number..." << std::endl;

        int prime = calculateNthPrime(num);
        std::cout << "[Child] Sending result for prime(" << num << ")..." << std::endl;

        std::string prime_str = std::to_string(prime);
        write(pipe2[1], prime_str.c_str(), prime_str.size() + 1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }
    else
    {
        close(pipe1[0]);
        close(pipe2[1]);

        std::cout << "[Parent] Please enter the number: ";
        std::string user_input;
        std::cin >> user_input;
        if (user_input == "exit")
        {
            write(pipe1[1], user_input.c_str(), user_input.size() + 1);
            close(pipe1[1]);
            close(pipe2[0]);
            exit(0);
        }

        if (!isValidNumber(user_input))
        {
            std::cout << "Invalid input" << std::endl;
            write(pipe1[1], "invalid", 7);
            close(pipe1[1]);
            close(pipe2[0]);
            return;
        }

        std::cout << "[Parent] Sending " << user_input << " to the child process..." << std::endl;

        write(pipe1[1], user_input.c_str(), user_input.size() + 1);

        std::cout << "[Parent] Waiting for response from the child process..." << std::endl;

        wait(nullptr);

        char result_buffer[20];
        memset(result_buffer, 0, sizeof(result_buffer));
        read(pipe2[0], result_buffer, sizeof(result_buffer));
        std::string result_str(result_buffer);
        std::cout << "[Parent] Received result for prime(" << user_input << ") = " << result_str << std::endl;
        close(pipe1[1]);
        close(pipe2[0]);
    }
}

int main()
{
    while (true)
    {
        primeNumberCalculator();
    }
}

