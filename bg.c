#include "bg.h"

void bg_command(char *all_args[100], int no_of_args)
{
    if (no_of_args != 2)
        printf("Incorrect number of arguments.\nFormat is `bg <jobNumber>`");

    else
    {
        int job_no = atoi(all_args[1]);
        if (job_no > process_no)
            printf("Enter valid job number\n");

        else
        {
            if (kill(processes[job_no - 1].pid, SIGCONT) < 0)
            {
                perror("");
            }
        }
    }
}