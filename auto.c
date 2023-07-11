#include "auto.h"

int isDira(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return -1;
    return S_ISDIR(statbuf.st_mode);
}

char *print_contents(char pres_dir[], char *input)
{
    char temp_dir[10000];

    if (pres_dir[0] == '~')
    {
        strcpy(temp_dir, home_dir);
        strcat(temp_dir, &pres_dir[1]);
        strcpy(pres_dir, temp_dir);
    }

    struct dirent **read;
    int count = scandir(pres_dir, &read, NULL, alphasort);
    if (count < 0)
        perror("Doesn't Exist\n");
    else
    {
        int ct = 0;
        char store[1000][1000];
        for (int x = 0; x < count; x++)
        {
            if (read[x]->d_name[0] == '.')
            {
                continue;
            }
            else
            {
                if (strncmp(read[x]->d_name, input, strlen(input)) == 0)
                {
                    char name[1000];
                    strcpy(name, read[x]->d_name);
                    // if (ct == 0)
                    //     printf("\n");

                    char filepath[2000];
                    int ch = 0;
                    strcpy(filepath, pres_dir);
                    strcat(filepath, "/");
                    strcat(filepath, read[x]->d_name);
                    ch = isDira(filepath);
                    if (ch == 1)
                    {
                        strcat(name, "/");
                        strcpy(store[ct], name);
                    }
                    else
                    {
                        strcat(name, " ");
                        
                        strcpy(store[ct], name);
                        // printf("%s\n",store[ct]);
                    }
                    ct++;
                }
            }
        }
        // printf("%d\n",ct);
        // printf("%s\n",store[0]);
        if (ct > 0)
        {
            if (ct == 1)
            {
                int p = 0;
                for (int i = 1; i < strlen(input); i++)
                {
                    if (input[i] != store[0][i])
                        break;
                    p++;
                }
                char *rem = &store[0][p + 1];
                autoc = 1;
                return rem;
            }
            else
            {
                printf("\n");
                for (int i = 0; i < ct; i++)
                    printf("%s\n", store[i]);

                display(fg_prompt, fg_prompt_flag);
                // printf("%s", input);

                int l = 2000;
                for (int i = 1; i < ct; i++)
                {
                    int sub = 0;
                    int l1 = strlen(store[i - 1]);
                    int l2 = strlen(store[i]);
                    int lmin = l1;
                    if (l1 > l2)
                        lmin = l2;
                    
                    // printf("%d\n", lmin);
                    for (int j = 0; j < lmin-1; j++)
                    {
                        if (store[i][j] == store[i - 1][j])
                            sub++;
                    }
                    // printf("%d ", sub);
                    if (l > sub)
                        l = sub;
                }
                // printf("%d\n", l);
                char subbuff[1000];
                memcpy(subbuff, &store[0][0], l);
                subbuff[l] = '\0';
                // printf("%s\n", subbuff);

                int p = -1;
                for (int i = 0; i < strlen(input); i++)
                {
                    if (input[i] != subbuff[i])
                        break;
                    p++;
                }
                if(p == -1)
                {
                    char* rem = &subbuff[0];;
                    return rem;
                }
                char *rem = &subbuff[p + 1];
                // printf("%s\n", rem);
                return rem;
                // return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }
}

char* autocomplete(char cwd[], char *input)
{
    // printf("%s\n",input);
    char* rem = print_contents(cwd, input);
    return rem;
}