// The purpose of this program is to be more powerful than the minishell and allow
// arguments to the commands. For every input to moreShell, it forks child processes.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 150
#define CWDSIZE 300

main() {
    pid_t pid;          // stores process identifier
    char cmd[SIZE];     // stores string from command line
    while ((strcmp(cmd, "exit")) != 0) {
        char cwd[CWDSIZE]; // cwd: current working directory ie. users/username/desktop
        char *position;
        int counter = 0;                        // word counter
        char *argv[11];                         // array of pointers
        char delimeter[] = " ";                 // delimeter is character that separates strings

        // if could not get cwd
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("Error! Could not get cwd.");
            return 1;
        }
        printf("moreShell:%s$ ", cwd); // user command
        fgets(cmd, SIZE, stdin);

        // if not null
        if ((position = strchr(cmd, '\n')) != NULL) {
            *position = ' ';
        }
        
        char *pointer = strtok(cmd, delimeter); // pointer to delimeter
        
        // pointer not zero
        while (pointer != 0) {
            argv[counter] = pointer;
            pointer = strtok(NULL, delimeter);
            counter++;
        }
        argv[counter] = NULL; // argv pointer is made equal to null to end array of pointers

        // cmd not exit
        if (strcmp(cmd, "exit") != 0) {
            pid = fork(); // fork child process

            // pid errors
            if (pid == 0){
                if (execvp(cmd, argv) == -1) {
                    printf("Does not recognize \"%s\" as a command or file!\n", cmd);
                    return -1;
                }
            }
            else if (pid < 0) {
                printf("pid error!");
            }
            // wait
            else {
                wait(NULL); // wait for child process to finish
            }
        }
        fflush(stdout); // flushes output buffer of stream
    }
}