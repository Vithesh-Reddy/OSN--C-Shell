#include "display.h"

void display(char prompt[100], int flag)
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        char *x = strstr(cwd, home_dir);
        if (x)
        {
            if (flag ==0)
                printf(KGRN "%s@%s" RESET KBLU ":~%s" RESET ">", user_name, host_name, strstr(cwd, home_dir) + strlen(home_dir));
            else
                printf(KGRN "%s@%s" RESET KBLU ":~%s" RESET "%s>", user_name, host_name, strstr(cwd, home_dir) + strlen(home_dir), prompt);
        }
        else
        {
            if (flag ==0)
                printf(KGRN "%s@%s" RESET KBLU ":~%s" RESET ">", user_name, host_name, cwd);
            else
                printf(KGRN "%s@%s" RESET KBLU ":~%s" RESET "%s>", user_name, host_name, cwd, prompt);
        }
    }
    else
    {
        perror("Error getting current directory");
    }
}