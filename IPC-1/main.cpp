#include <pwd.h>
#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

#include <csignal>
#include <cstring>
#include <iostream>

void signal_handler(int signal, siginfo_t* signal_info, void* context_info)
{
    ucontext_t* context = (ucontext_t*)context_info;

    struct passwd* user_info = getpwuid(signal_info->si_uid);
    printf("Received a SIGUSR1 signal from process[%d] executed by[%d]([%s]).\n", signal_info->si_pid, signal_info->si_uid,
           user_info->pw_name);
    printf("State of the context: RIP = [%lld], RAX = [%lld], RBX = [%lld]. \n", context->uc_mcontext.gregs[REG_RIP],
           context->uc_mcontext.gregs[REG_RAX], context->uc_mcontext.gregs[REG_RBX]);
}

int main()
{
    struct sigaction sig_action;
    memset(&sig_action, 0, sizeof(sig_action));
    sig_action.sa_sigaction = signal_handler;
    sig_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig_action, nullptr);
    std::cout << "Waiting for SIGUSR1...\n";
    while (true) sleep(10);
}

