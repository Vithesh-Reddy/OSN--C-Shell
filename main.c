#include "main.h"

int main()
{
    printf("----------------------The shell starts here-----------------------\n");
    gethostname(host_name, sizeof(host_name));
    getlogin_r(user_name, sizeof(user_name));

    getcwd(cwd, sizeof(cwd));
    getcwd(home_dir, sizeof(home_dir));
    strcpy(prev_dir, "");

    signal(SIGCHLD, handler);
    signal(SIGINT, signal_control_c);
    signal(SIGTSTP, signal_control_z);
    InFile = dup(STDIN_FILENO);
    OutFile = dup(STDOUT_FILENO);
    spid = getpid();
    spgid = getpgid(spid);
    fg_prompt_flag = 0;
    fg_time = 0;
    fg_ch = 0;
    autoc = 0;

    while (1)
    {
        display(fg_prompt, fg_prompt_flag);
        fflush(stdout);
        fg_prompt_flag = 0;
        fg_time = 0;
        fg_ch = 0;
        char *lineptr = input();
        if (lineptr[0] == '\0')
            continue;

        if (lineptr[0] == ' ' || lineptr[0] == '\t')
        {
            perror("Command Not Found");
            continue;
        }

        int no_of_commands = tokenize1(lineptr);
        int j = 0;
        while (j < no_of_commands)
        {
            if (strstr(all_commands[j], "|"))
                pipe_command(all_commands[j]);
            else
                implement(all_commands[j]);
            j++;
        }
    }
}