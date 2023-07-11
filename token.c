#include "token.h"

int tokenize1(char *lineptr)
{
    int no_of_commands = 0;
    char *token1 = strtok(lineptr, ";");
    if (token1 != NULL)
    {
        all_commands[no_of_commands++] = token1;
    }
    while (token1 != NULL)
    {
        token1 = strtok(NULL, ";");
        if (token1 != NULL)
        {
            all_commands[no_of_commands++] = token1;
        }
    }
    return no_of_commands;
}

int tokenize2(char command[], char *all_args[100])
{

    int count = 0;
    char *token2 = strtok(command, " \t\n");
    if (token2 != NULL)
    {
        all_args[count++] = token2;
    }
    while (token2 != NULL)
    {
        token2 = strtok(NULL, " \t\n");
        if (token2 != NULL)
        {
            all_args[count++] = token2;
        }
    }
    return count;
}

int tokenize3(char str[], char *pipe_commands[100])
{
    int i = 0;
    char *token = strtok(str, "|");
    if (token != NULL)
        pipe_commands[i++] = token;
    while (token != NULL)
    {
        token = strtok(NULL, "|");
        if (token != NULL)
            pipe_commands[i++] = token;
    }
    return i;
}
