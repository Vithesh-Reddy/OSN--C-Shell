#include "pinfo.h"

void pinfo_command(char *all_args[100])
{

    char path[2000], pid[101];
    unsigned long mem;
    int str_size;

    char exe[2000], status[101];

    if (all_args[1] && (strcmp(all_args[1], "")))
    {
        strcpy(pid, all_args[1]);
    }
    else
    {
        int x = getpid();
        sprintf(pid, "%d", x);
    }

    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/stat");
    FILE *file_pointer = fopen(path, "r");

    int flag = 0; // for +
    if (file_pointer == NULL)
    {
        printf("Error opening %s file\n", path);
        return;
    }
    else
    {
        long long pgrp, tpgid;
        char str[2000];
        int i = 1;
        while (fscanf(file_pointer, "%s", str) == 1)
        {
            if (i == 3)
            {
                strcpy(status, str);
            }
            if (i == 5)
                pgrp = atoi(str);
            if (i == 8)
            {
                tpgid = atoi(str);
            }
            if (i == 23)
            {
                mem = atoi(str);
                break;
            }
            i++;
        }

        if (pgrp == tpgid)
            flag = 1;
        else
            flag = 0;

        fclose(file_pointer);
    }

    printf("pid -- %s\n", pid);
    printf("Process Status -- {%s", status);

    if (flag)
        printf("+");
    printf("}\n");

    printf("Memory -- %ld bytes {​Virtual Memory​}\n", mem);

    strcpy(path, "/proc/");
    strcat(path, pid);
    strcat(path, "/exe");
    str_size = readlink(path, exe, sizeof(exe)); // get exe path data
    exe[str_size] = '\0';                        // null terminate

    char *sub;
    char f_print[1000];
    strcpy(f_print, "~");
    sub = strstr(exe, home_dir);
    if (sub != NULL)
    {
        sub = sub + strlen(home_dir);
        strcat(f_print, sub);
        printf("Executable Path -- %s\n", f_print);
    }

    else
        printf("Executable Path -- %s\n", exe);
}