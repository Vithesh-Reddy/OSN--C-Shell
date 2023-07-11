#include "discover.h"

int isDir(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return -1;
    return S_ISDIR(statbuf.st_mode);
}

int isFil(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return -1;
    return S_ISREG(statbuf.st_mode);
}

void only_discover(char pres_dir[], char use_dir[], char use_path[], char name[])
{

    char temp_dir[10000];
    // printf("%s\n", pres_dir);
    if (use_dir[0] == '~')
    {
        strcpy(temp_dir, home_dir);
        strcat(temp_dir, &use_dir[1]);
        strcpy(use_dir, temp_dir);
    }
    // printf("%s\n", use_dir);

    int ch = isFil(use_dir);
    if (ch == -1)
    {
        perror("ERROR");
        return;
    }
    if (ch == 1)
    {
        perror("ERROR");
    }
    else
    {
        ch = isDir(use_dir);
        // printf("%d\n", ch);
        if (ch == -1)
        {
            perror("ERROR");
            return;
        }
        if (ch == 1)
        {
            struct dirent **read;
            int count = scandir(use_dir, &read, NULL, alphasort);

            char child_dir[10000];
            char print_path[10000];
            char use_path_it[10000];
            if (count >= 0)
            {
                for (int x = 0; x < count; x++)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        continue;
                    }
                    strcpy(print_path, use_path);
                    strcat(print_path, "/");
                    strcat(print_path, read[x]->d_name);

                    if (name == NULL)
                        printf("%s\n", print_path);
                    else
                    {
                        if (strcmp(strrchr(print_path, '/') + 1, name) == 0)
                            printf("%s\n", print_path);
                    }

                    strcpy(child_dir, use_dir);
                    strcat(child_dir, "/");
                    strcat(child_dir, read[x]->d_name);

                    ch = isDir(child_dir);
                    if (ch == 1)
                    {
                        only_discover(pres_dir, child_dir, print_path, name);
                    }
                }
            }
        }
    }
}

void only_dirs(char pres_dir[], char use_dir[], char use_path[], char name[])
{
    char temp_dir[10000];
    // printf("%s\n", pres_dir);
    if (use_dir[0] == '~')
    {
        strcpy(temp_dir, home_dir);
        strcat(temp_dir, &use_dir[1]);
        strcpy(use_dir, temp_dir);
    }
    // printf("%s\n", use_dir);

    int ch = isFil(use_dir);
    if (ch == -1)
    {
        perror("ERROR");
        return;
    }
    if (ch == 1)
    {
        perror("ERROR");
    }
    else
    {
        ch = isDir(use_dir);
        // printf("%d\n", ch);
        if (ch == -1)
        {
            perror("ERROR");
            return;
        }
        if (ch == 1)
        {
            struct dirent **read;
            int count = scandir(use_dir, &read, NULL, alphasort);

            char child_dir[10000];
            char print_path[10000];
            char use_path_it[10000];
            if (count >= 0)
            {
                for (int x = 0; x < count; x++)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        continue;
                    }
                    strcpy(child_dir, use_dir);
                    strcat(child_dir, "/");
                    strcat(child_dir, read[x]->d_name);

                    ch = isDir(child_dir);
                    if (ch == 1)
                    {
                        strcpy(print_path, use_path);
                        strcat(print_path, "/");
                        strcat(print_path, read[x]->d_name);

                        if (name == NULL)
                            printf("%s\n", print_path);
                        else
                        {
                            if (strcmp(strrchr(print_path, '/') + 1, name) == 0)
                                printf("%s\n", print_path);
                        }

                        only_dirs(pres_dir, child_dir, print_path, name);
                    }
                }
            }
        }
    }
}

void only_files(char pres_dir[], char use_dir[], char use_path[], char name[])
{
    char temp_dir[10000];
    // printf("%s\n", name);
    if (use_dir[0] == '~')
    {
        strcpy(temp_dir, home_dir);
        strcat(temp_dir, &use_dir[1]);
        strcpy(use_dir, temp_dir);
    }

    int ch = isFil(use_dir);
    if (ch == -1)
    {
        perror("ERROR");
        return;
    }
    if (ch == 1)
    {
        perror("ERROR");
    }
    else
    {
        ch = isDir(use_dir);

        if (ch == -1)
        {
            perror("ERROR");
            return;
        }
        if (ch == 1)
        {
            struct dirent **read;
            int count = scandir(use_dir, &read, NULL, alphasort);

            char child_dir[10000];
            char print_path[10000];
            char use_path_it[10000];
            if (count >= 0)
            {
                for (int x = 0; x < count; x++)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        continue;
                    }
                    strcpy(print_path, use_path);
                    strcat(print_path, "/");
                    strcat(print_path, read[x]->d_name);

                    strcpy(child_dir, use_dir);
                    strcat(child_dir, "/");
                    strcat(child_dir, read[x]->d_name);

                    ch = isFil(child_dir);
                    if (ch == 1)
                    {
                        if (name == NULL)
                            printf("%s\n", print_path);
                        else
                        {
                            if (strcmp(strrchr(print_path, '/') + 1, name) == 0)
                                printf("%s\n", print_path);
                        }
                    }

                    ch = isDir(child_dir);
                    if (ch == 1)
                    {
                        only_files(pres_dir, child_dir, print_path, name);
                    }
                }
            }
        }
    }
}

void discover_command(char *all_args[100], char pres_dir[], int k)
{
    if (k == 1)
    {
        only_discover(pres_dir, pres_dir, ".", NULL);
        return;
    }
    int flag_d, flag_f, flag_dir, flag_name;
    flag_d = flag_dir = flag_f = flag_name = 0;

    for (int i = 0; i < k; i++)
    {
        if (strcmp(all_args[i], "-d") == 0)
            flag_d++;
        else if (strcmp(all_args[i], "-f") == 0)
            flag_f++;
        else if (all_args[i][0] == '"')
            flag_name++;
        else if (strcmp(all_args[i], "discover") != 0)
            flag_dir++;
    }

    // printf("%d %d %d %d\n", flag_dir, flag_name, flag_d, flag_f);
    if (flag_d == 0 && flag_f == 0)
    {
        if (flag_dir == 0)
        {
            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[1][strlen(all_args[1])-1] = '\0';
                memcpy(subtext, &all_args[1][1], strlen(all_args[1])-1);
                subtext[strlen(all_args[1])-1] = '\0';
            
                only_discover(pres_dir, pres_dir, ".", subtext);
            }
        }
        else
        {
            char path[2000];
            if (strstr(all_args[1], "~"))
            {
                strcpy(path, home_dir);
                strcat(path, all_args[1] + 1);
            }
            else
                strcpy(path, all_args[1]);

            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[2][strlen(all_args[2])-1] = '\0';
                memcpy(subtext, &all_args[2][1], strlen(all_args[2])-1);
                subtext[strlen(all_args[2])-1] = '\0';
                
                only_discover(pres_dir, path, ".", subtext);
            }
            else
                only_discover(pres_dir, path, ".", NULL);
        }
    }

    else if (flag_f == 0 && flag_d == 1)
    {
        if (flag_dir == 0)
        {
            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[2][strlen(all_args[2])-1] = '\0';
                memcpy(subtext, &all_args[2][1], strlen(all_args[2])-1);
                subtext[strlen(all_args[2])-1] = '\0';

                only_dirs(pres_dir, pres_dir, ".", subtext);
            }

            else
                only_dirs(pres_dir, pres_dir, ".", NULL);
        }
        else
        {
            char path[2000];
            if (strstr(all_args[1], "~"))
            {
                strcpy(path, home_dir);
                strcat(path, all_args[1] + 1);
            }
            else
                strcpy(path, all_args[1]);

            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[3][strlen(all_args[3])-1] = '\0';
                memcpy(subtext, &all_args[3][1], strlen(all_args[3])-1);
                subtext[strlen(all_args[3])-1] = '\0';

                only_dirs(pres_dir, path, ".", subtext);
            }
            else
                only_dirs(pres_dir, path, ".", NULL);
        }
    }

    else if (flag_f == 1 && flag_d == 0)
    {
        if (flag_dir == 0)
        {
            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[2][strlen(all_args[2])-1] = '\0';
                memcpy(subtext, &all_args[2][1], strlen(all_args[2])-1);
                subtext[strlen(all_args[2])-1] = '\0';
                
                only_files(pres_dir, pres_dir, ".", subtext);
            }
            else
                only_files(pres_dir, pres_dir, ".", NULL);
        }
        else
        {
            char path[2000];
            if (strstr(all_args[1], "~"))
            {
                strcpy(path, home_dir);
                strcat(path, all_args[1] + 1);
            }
            else
                strcpy(path, all_args[1]);

            if (flag_name == 1)
            {
                char subtext[1000];
               all_args[3][strlen(all_args[3])-1] = '\0';
                memcpy(subtext, &all_args[3][1], strlen(all_args[3])-1);
                subtext[strlen(all_args[3])-1] = '\0';

                only_files(pres_dir, path, ".", subtext);
            }
            else
                only_files(pres_dir, path, ".", NULL);
        }
    }

    else if (flag_f == 1 && flag_d == 1)
    {
        if (flag_dir == 0)
        {
            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[3][strlen(all_args[3])-1] = '\0';
                memcpy(subtext, &all_args[3][1], strlen(all_args[3])-1);
                subtext[strlen(all_args[3])-1] = '\0';
                
                only_discover(pres_dir, pres_dir, ".", subtext);
            }
            else
                only_discover(pres_dir, pres_dir, ".", NULL);
        }
        else
        {
            char path[2000];
            if (strstr(all_args[1], "~"))
            {
                strcpy(path, home_dir);
                strcat(path, all_args[1] + 1);
            }
            else
                strcpy(path, all_args[1]);

            if (flag_name == 1)
            {
                char subtext[1000];
                all_args[4][strlen(all_args[4])-1] = '\0';
                memcpy(subtext, &all_args[4][1], strlen(all_args[4])-1);
                subtext[strlen(all_args[4])-1] = '\0';

                only_discover(pres_dir, path, ".", subtext);
            }
            else
                only_discover(pres_dir, path, ".", NULL);
        }
    }
}