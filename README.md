# Work

1. Display Requirement

- On execution of the code, a shell prompt of the following form appears:
<username@system_name:curr_dir>

- The directory from which the shell is invoked will be the home directory of the shell and is indicated by "~"

- On changing the directory using cd, the change in directory is reflected in the shell as well.

2. Builtin Commands

- echo : Prints the given argument on the shell. Multi-line strings and environmental variables are not handled. Escape flags and quotes are not handled. 
- pwd : Prints the full pathname of the current working directory.
- cd : changes the directory. Handles the flags '.', '..', '-' and '~'. If no argument is present, then cd changes the directory to the home directory. 

3. ls command

- Implemented :
  - ls
  - ls -l
  - ls -a
  - ls -al/-la
  - ls <dir1> <dir2> -a/-l/-al/-la

- Used colour coding: Directories - Blue, Executables - Green, Files - White
- Order of arguments doesn't matter
- The output is very similar to the bash shell output

4. System Commands (fg and bg)

- Foreground: 
  - Shell waits for this process to complete and regains control when this process exits.
  - Time taken by the foreground process is printed in the next prompt if the process takes atleast 1 second to run.
  - Incase of multiple foreground processes, I have printed the total time taken by them in the next prompt.
  - Time taken by foreground processes is not considered if the time is less than 1 second.

- Background:
  - Any command invoked with "&" is treated as a background command.
  - Shell will spawn that process and doesn't wait for the process to exit. It will keep taking other user commands.
  - Whenever a new background process is started, I print the process number and PID of the newly created background process.
  - I print the process name along with its pid when a background process finishes. 

5. pinfo command

- pinfo prints the process-related info of the shell program.
- pinfo <pid> prints the process info of the given pid.

6. Discover

- The command will have the following optional command line arguments:
  - discover <target_dir> <type_flags> <file_name>
- type_flags are -f and -d
  - -f prints all the files
  - -d prints all the directories
  - if both or none of -d and -f are specified, I print all the contents
- file_name indicates that only the contents with name = file_name must be printed.
- Order of arguments is fixed.
- I print the contents of the target directory relative to the target directory.
- If no target_dir is specified, the current directory is taken as the target directory.

7. History

- The latest entered commands are displayed.
- The default number of commands displayed is 10.
  - In case less the number of commands are less than 10, I print all the commands.
  - Else, I print the latest 10.
- The default number of commands the history stores is 20.
- I overwrite the oldest commands if more than 20 commands are entered.
- I track the commands across all sessions and not just one.
- I do not store the command in history if it is the exactly same as the previously entered command.
- I store the command history in command_history.txt file present in the home directory of the created shell.

8. I/O Redirection

- Using the symbols <, > and >>; the output of commands, usually written to stdout, can be redirected to another file or the input taken from a file other than stdin.
- Both input and output redirection can be used simultaneously.
- The output file is created (with permissions 0644)if it does not already exist.
- In case the output file already exists, it is overwritten in case of > and appended to in case of >>.
- Multiple inputs and outputs are not handled.

9. Command Pipelines

- A pipe, identified by |, redirects the output of the command on the left as input to the command on the right.
- One or more commands can be piped.

10. I/O Redirection within Command Pipelines

- Input/output redirection can occur within command pipelines.

11. User-defined Commands

- jobs:
  - This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number, process ID, and their state, which can either be running or stopped. 
  - Flags -r and -s can be specified along with jobs. If the flag specified is -r, it prints only the running processes else if the flag is -s, it prints the stopped processes only.
- sig:
  - Takes the job number of a running job and sends the signal corresponding to the signal number to that process.
- fg:
  - Brings the running or stopped background job corresponding to job number to the foreground, and changes its state to running.
- bg:
  - Changes the state of a stopped background job to running (in the background).
  - Does nothing if the job is already running in the background.

12. Signal Handling

- CTRL Z:
  - It pushes any currently running foreground job into the background, and changes its state from 'running' to 'stopped'.
- CTRL C:
  - It interrupts any currently running foreground job, by sending it the SIGINT signal.
- CTRL D:
  - It logs out of the shell.

13. Autocomplete

- The tab key can be pressed at any time of the prompt.
- When the tab key is pressed:
  - Searches for the contents (files/directories) in the current working directory starting with the name specified in the command.
  - If there's only one such file/directory, it's autocompleted.
  - If there are more such files/directories, all of them are printed line by line after which a new promt is displayed with the common letters in those files completed in the name.
  - If there are no such files, nothing is done.
  - If it's a file, a space is placed after the file. If it’s a folder, a ‘/’ is put after the folder name.


# Assumptions

- Number of commands is less than 100
- Number of arguments in a command is less than 100
- The lenght of filename/directory names is less than 1000


**Note** - Error handling is done for all the cases. Tabs and spaces have been taken care of in all the commands. Tokenization has been done for the commands.

# Modules

- main.h and main.c : Contain the basic code to run the shell.
- display.h and display.c : To display shell prompt.
- implement.h and implement.c : To implement the functionality of a command.
- input.h and input.c : To take the input commands from the user.
- part.h and part.c : To identify each command.
- token.h and token.c : To tokenize the input (tokenize1) and each command (tokenize2) of the input. Also,to tokenize pipe commands (tokenize3).
- echo.h and echo.c : To implement the echo command.
- pwd.h and pwd.c : To implement the pwd command.
- cd.h and cd.c : To implement the cd command.
- ls.h and ls.c : To implement the ls command.
- fg_bg.h, fg_bg.c, signal.h, signal.c : To implement the foreground and background processes' functionality.
- pinfo.h and pinfo.c : To implement the pinfo command.
- discover.h and discover.c : To implement the discover command.
- history.h and history.c : To implement the history command.
- pipe.h and pipe.c : To implement the pipe command.
- redirect.h and redirect.c : To implement the redirect command.
- tab.h and tab.c : To take input and detect tab.
- auto.h and auto.c : To implement autocomplete feature.
- job.h and job.c : To implement the jobs feature.
- sig.h and sig.c : To implement the sig feature.
- fg.h and fg.c : To implement the fg feature.
- bg.h and bg.c : To implement the bg feature.
- makefile : To compile the scripts.