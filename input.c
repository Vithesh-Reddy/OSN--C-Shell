#include "input.h"
#include "tab.c"
#include "auto.c"

char *input()
{
    char *inp = malloc(sizeof(char) * 100);
    char c;

    setbuf(stdout, NULL);
    enableRawMode();
    // printf("Prompt>");
    memset(inp, '\0', 100);
    int pt = 0;
    int tab = 0;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            if (c == 10)
                break;
            else if (c == 27)
            {
                char buf[3];
                buf[2] = 0;
                // if (read(STDIN_FILENO, buf, 2) == 2)
                // { // length of escape code
                //     printf("\rarrow key: %s", buf);
                // }
            }
            else if (c == 127)
            { // backspace
                if (pt > 0)
                {
                    if (inp[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    inp[--pt] = '\0';
                    printf("\b \b");
                }
            }
            else if (c == 9)
            { // TAB character
              // inp[pt++] = c;
              // for (int i = 0; i < 8; i++)
              // { // TABS should be 8 spaces
              //     printf(" ");
              // }
                // printf("%d", tab);
                // printf("%s", &inp[tab]);
                char *rem = autocomplete(cwd, &inp[tab]);
                // printf("%s\n", rem);
                if (rem != NULL)
                {
                    // printf("NULLLL");
                    for (int k = 0; k < strlen(rem); k++)
                    {
                        inp[pt++] = rem[k];
                        if (autoc == 1)
                            printf("%c", rem[k]);
                    }
                    if (autoc == 0)
                        printf("%s", inp);
                }
                autoc = 0;
            }
            else if (c == 4 || c == EOF)
            {
                printf("\n");
                exit(0);
            }
            else
            {
                printf("%d\n", c);
            }
        }
        else
        {
            inp[pt++] = c;
            if (c == ' ')
                tab = pt;
            printf("%c", c);
        }
    }
    disableRawMode();
    // inp[strlen(inp)-1] = '\0';
    // printf("%s\n", inp);
    printf("\n");
    write_history(inp);

    return inp;
}