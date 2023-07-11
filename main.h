#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>

#include "display.h"
#include "implement.h"
#include "part.h"
#include "token.h"
#include "input.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "signal.h"
#include "fg_bg.h"
#include "pinfo.h"
#include "discover.h"
#include "history.h"
#include "job.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "tab.h"
#include "auto.h"
#include "redirect.h"
#include "pipe.h"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define RESET "\x1B[0m"

char host_name[1000];
char user_name[1000];
char cwd[1000];
char home_dir[1000];
char *all_commands[100];
char prev_dir[1000];
char fg_prompt[100];
int fg_prompt_flag;
long int fg_time;
int fg_ch;
int autoc;

struct Node
{
    char process_name[101];
    pid_t pid;
};
struct job_d
{
    int num;
    char stat_info[20];
    char name[100];
    int pid;
};
int InFile, OutFile;
pid_t spid;
pid_t spgid;
typedef struct job_d job_d;
typedef struct Node node;
node processes[100];
int process_no;

#endif