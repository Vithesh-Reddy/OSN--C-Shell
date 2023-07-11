#include "implement.h"

void implement(char command[])
{
    char new_command[1000];
    strcpy(new_command, command);
    char *all_args[100];
    memset(all_args, 0, sizeof(all_args));
    int no_of_args = tokenize2(command, all_args);

    part(all_args, no_of_args, new_command);
}