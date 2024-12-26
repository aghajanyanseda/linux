#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

void split_input(char *input_str, char **arg_list)
{
    char *token = strtok(input_str, " ");
    int arg_index = 0;
    while (token != nullptr)
    {
        arg_list[arg_index++] = token;
        token = strtok(nullptr, " ");
    }
    arg_list[arg_index] = nullptr;
}

bool is_exit_command(char *cmd)
{
    char *ptr = cmd;
    while (*ptr == ' ') ptr++;
    return (strncmp(ptr, "exit", 4) == 0);
}

int execute_command(char *cmd_str)
{
    if (is_exit_command(cmd_str)) return 1;

    char *argv[256];
    char *redirection_file = strchr(cmd_str, '>');
    bool append_mode = false;

    if (redirection_file != nullptr)
    {
        *redirection_file = '\0';
        redirection_file++;
        if (*redirection_file == '>')
        {
            append_mode = true;
            *redirection_file = '\0';
            redirection_file++;
        }
        while (*redirection_file == ' ' || *redirection_file == '\t') redirection_file++;
    }

    pid_t child_pid = fork();
    if (child_pid < 

