#include "part.h"

void part(char *all_args[100], int no_of_args, char new_command[])
{
    int bg_flag = 0;
    int i;
    for (i = 0; i < no_of_args; i++)
    {
        int ch = 0;
        int j;

        // if (!strcmp(all_args[i], "&"))
        if (all_args[i][strlen(all_args[i]) - 1] == '&')
        {
            bg_flag = 1;
            all_args[i][strlen(all_args[i]) - 1] = '\0';
            break;
        }
    }
    if (strstr(new_command, "<") || strstr(new_command, ">"))
    {
        int x = redirect(new_command, all_args, no_of_args);
        if (x == 1)
            return;
        for (int i = 0; i < no_of_args; i++)
        {
            if (!strcmp(all_args[i], ">") || !strcmp(all_args[i], ">>") || !strcmp(all_args[i], "<"))
            {
                fprintf(stderr, "Invalid Syntax\n");
                return;
            }
        }
    }
    if (!strcmp(all_args[0], "quit"))
    {
        exit(0);
    }

    else if (!strcmp(all_args[0], "cd"))
    {
        cd_command(all_args, no_of_args);
    }

    else if (!strcmp(all_args[0], "pwd"))
    {
        pwd_command();
    }

    else if (!strcmp(all_args[0], "echo"))
    {
        echo_command(all_args, no_of_args);
    }

    else if (!strcmp(all_args[0], "ls"))
    {
        ls_command(all_args, cwd, no_of_args);
    }

    else if (!strcmp(all_args[0], "pinfo"))
    {
        pinfo_command(all_args);
    }

    else if (!strcmp(all_args[0], "discover"))
    {
        discover_command(all_args, cwd, no_of_args);
    }

    else if (!strcmp(all_args[0], "history"))
    {
        history_command(all_args, cwd, no_of_args);
    }
    else if (!strcmp(all_args[0], "jobs"))
    {
        job_command(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "sig"))
    {
        sig_command(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "fg"))
    {
        fg_command(all_args, no_of_args);
    }
    else if (!strcmp(all_args[0], "bg"))
    {
        bg_command(all_args, no_of_args);
    }
    else if (bg_flag && i == no_of_args - 1)
    {
        // for (int p = 0; p < no_of_args; p++)
        //     printf("%s\n", all_args[i]);
        fbbg(all_args, 1, no_of_args);
    }
    else if (bg_flag && i != no_of_args - 1)
    {
        char *new_args[100];
        int k = 0;
        for (int j = i + 1; j < no_of_args; j++)
        {
            new_args[k++] = all_args[j];
            all_args[j] = "";
        }
        // for (int p = 0; p < no_of_args; p++)
        //     printf("%s\n", all_args[i]);
        fbbg(all_args, 1, no_of_args);
        part(new_args, no_of_args - i - 1, new_command);
    }

    else
    {
        fg_ch++;
        fbbg(all_args, 0, no_of_args);
    }
    dup2(InFile, STDIN_FILENO);
    dup2(OutFile, STDOUT_FILENO);
}