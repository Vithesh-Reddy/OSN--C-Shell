#include "fg_bg.h"

void fbbg(char *all_args[100], int bg, int no_of_args)
{

    int j = 0;
    for (int i = 0; i < no_of_args; i++)
    {
        if (strcmp(all_args[i], ""))
        {
            all_args[j++] = all_args[i];
        }
    }
    all_args[j] = 0;

    int status;
    pid_t pid = fork();
    pid_t wpid;

    all_args[no_of_args] = NULL;

    if (pid < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) // child
    {
        setpgid(0, 0);                         // sets pgid of child to 0
        if (execvp(all_args[0], all_args) < 0) // executes child
        {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
    else // parent
    {
        if (bg == 0)
        {
            char CURR[1024];
            strcpy(CURR, all_args[0]);

            for (int i = 1; i < j; i++)
            {
                strcat(CURR, " ");
                strcat(CURR, all_args[i]);
            }

            signal(SIGTTIN, SIG_IGN);     // ignore input
            signal(SIGTTOU, SIG_IGN);     // ignore output
            tcsetpgrp(STDIN_FILENO, pid); // set fg id
            time_t rawtime;
            struct tm *timeinfo;

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            wpid = waitpid(pid, &status, WUNTRACED);

            time_t rawtime2;
            struct tm *timeinfo2;

            time(&rawtime2);
            timeinfo2 = localtime(&rawtime2);

            time_t const timediff = rawtime2 - rawtime;
            if (timediff >= 1)
            {
                fg_prompt_flag++;
                fg_time += timediff;
                sprintf(fg_prompt, "took %lds", fg_time);
                // display(fg_prompt, fg_prompt_flag);
                // printf("\n");
            }

            tcsetpgrp(STDIN_FILENO, getpgrp()); // get fg id
            signal(SIGTTIN, SIG_DFL);           // default input
            signal(SIGTTOU, SIG_DFL);           // default output

            if (WIFSTOPPED(status))
            {
                printf("%s with PID %d suspended\n", CURR, pid);
                strcpy(processes[process_no].process_name, CURR);
                processes[process_no].pid = pid;
                process_no++;
            }
        }

        else
        {
            strcpy(processes[process_no].process_name, all_args[0]);

            for (int i = 1; i < j; i++)
            {
                strcat(processes[process_no].process_name, " ");
                strcat(processes[process_no].process_name, all_args[i]);
            }

            processes[process_no].pid = pid;
            process_no++;
            printf("[%d] %d\n", process_no, pid);
        }
    }

    return;
}