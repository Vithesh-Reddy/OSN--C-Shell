#include "main.h"

void handler(int signal)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        char str[2000];
        bool flag = false;

        for (int i = 0; i < process_no; i++)
        {
            if (processes[i].pid == pid)
            {
                strcpy(str, processes[i].process_name);
                flag = true;
                break;
            }
        }
        if (flag)
        {
            if (WEXITSTATUS(status) == 0 && WIFEXITED(status))
                fprintf(stderr, "\n%s with PID %d exited normally\n", str, pid);
            // printf("\n%s with PID %d exited normally\n", str, pid);

            else
                fprintf(stderr, "\n%s with PID %d failed to exit normally\n", str, pid);

            if (fg_ch != 0)
                printf("\n");
            else
                display(fg_prompt, 0);
            fflush(stdout);
        }

        return;
    }
}

void signal_control_c(int sig)
{

    printf("\n");
    display(fg_prompt, fg_prompt_flag);
    fflush(stdout);
}

void signal_control_z(int sig)
{

    printf("\n");
    display(fg_prompt, fg_prompt_flag);
    fflush(stdout);
    
}