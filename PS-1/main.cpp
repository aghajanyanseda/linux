#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <iostream>

void execute_command(char **command_args)
{
    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        std::cout << "Fork failed" << std::endl;
        return;
    }
    else if (child_pid == 0)
    {
        execvp(command_args[0], command_args);
        std::cerr << "Execution failed" << std::endl;
        exit(1);
    }
    else
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        int child_status;
        waitpid(child_pid, &child_status, 0);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> execution_duration = end_time - start_time;

        if (WIFEXITED(child_status))
        {
            std::cout << "Exit status: " << WEXITSTATUS(child_status) << std::endl;
        }
        else if (WIFSIGNALED(child_status))
        {
            std::cout << "Command terminated by signal: " << WTERMSIG(child_status) << std::endl;
        }

        std::cout << "Duration: " << execution_duration.count() << " seconds" << std::endl;
    }
}

int main(int argc, char **args)
{
    if (argc == 1)
    {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }
    execute_command(args + 1);
    return 0;
}
}

