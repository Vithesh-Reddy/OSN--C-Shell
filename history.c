#include "history.h"

void history_command(char *all_args[100], char pres_dir[], int k)
{
    if (k > 1)
    {
        perror("Too many arguments");
        return;
    }

    char history_file[2000];
    strcpy(history_file, home_dir);
    strcat(history_file, "/command_history.txt");

    FILE *fp;

    fp = fopen(history_file, "r");

    int ct = 0;
    char his[25][1000];

    if (fp == NULL)
    {
        perror("No history");
        return;
    }
    else
    {
        size_t chars = 0;
        size_t len = 0;
        char *line = NULL;

        while ((chars = getline(&line, &len, fp)) != -1)
        {
            line[chars - 1] = '\0';
            strcpy(his[ct++], line);
        }
    }
    fclose(fp);

    if (ct <= 10)
    {
        for (int i = 0; i < ct; i++)
            printf("%s\n", his[i]);
    }
    else
    {
        for (int i = ct-10; i < ct; i++)
            printf("%s\n", his[i]);
    }

    return;
}

void write_history(char command[1000])
{
    char history_file[2000];
    strcpy(history_file, home_dir);
    strcat(history_file, "/command_history.txt");

    FILE *fp;

    fp = fopen(history_file, "ab+");

    char c;
    int count = 0;
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
            count = count + 1;
    }
    // printf("%d\n", count);

    fseek(fp, 0, SEEK_SET);

    if (count < 20)
    {
        size_t chars = 0;
        size_t len = 0;
        char *line = NULL;

        char his[25][1000];
        int ct = 0;

        while ((chars = getline(&line, &len, fp)) != -1)
        {
            line[chars - 1] = '\0';
            strcpy(his[ct++], line);
        }
        // fseek(fp, 0, SEEK_SET);

        if (strcmp(his[ct - 1], command) != 0)
        {
            fprintf(fp, "%s\n", command);
            // fseek(fp, 0, SEEK_SET);
        }
    }
    else
    {
        size_t chars = 0;
        size_t len = 0;
        char *line = NULL;

        char his[25][1000];
        int ct = 0;

        while ((chars = getline(&line, &len, fp)) != -1)
        {
            line[chars - 1] = '\0';
            strcpy(his[ct++], line);
        }
        // fseek(fp, 0, SEEK_SET);
        if (strcmp(his[ct - 1], command) != 0)
        {
            for (int i = 0; i < ct - 1; i++)
                strcpy(his[i], his[i + 1]);

            strcpy(his[ct - 1], command);

            // for (int i = 0; i < ct; i++)
            //     printf("%s\n", his[i]);

            fclose(fp);
            FILE *fpn;

            fpn = fopen(history_file, "w");

            for (int i = 0; i < ct; i++)
                fprintf(fp, "%s\n", his[i]);
        }
    }
    fclose(fp);
}