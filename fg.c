#include "fg.h"

void fg_command(char *all_args[100], int no_of_args)
{
    char CURR[100];
    if (no_of_args != 2)
    {
        printf("Incorrect number of arguments.\nFormat is `fg <jobNumber>`\n");
        return;
    }
    int pid, job_no = atoi(all_args[1]), status;
    if (job_no > process_no)
    {
        printf("Enter valid job number\n");
        return;
    }
    pid = processes[job_no - 1].pid;
    // printf("pid,%d ",pid);
    strcpy(CURR, processes[job_no - 1].process_name);
    // del_pro(job_no - 1);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);
    kill(pid, SIGCONT);

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    waitpid(pid, &status, WUNTRACED);

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

    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (WIFSTOPPED(status))
    {
        printf("%s with PID %d suspended\n", CURR, pid);
        // strcpy(processes[p_no].pro_name, CURR);
        // processes[p_no].PID = pid;
        // p_no++;
    }

    return;
}