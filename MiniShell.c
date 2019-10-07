#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_SIZE 100

int main()
{
    //stores the entered command
    char command[MAX_SIZE];

    //stores pid
    pid_t pid;

    while ((strcmp(command, "exit")) != 0)
    {
        printf("MiniShell$ ");
        fgets(command, MAX_SIZE, stdin);

        char *argv[2];
        char *newLine;
        
        if ((newLine=strchr(command, '\n')) != NULL)
            *newLine = '\0';

        argv[0] = command;
        argv[1] = NULL; //stop array pointer that are NULL

        if (strcmp(command, "exit") != 0)
	{
            //fork the child process
            pid = fork();

            if (pid < 0)
	    {
                printf("Error in PID");
            }
            else if (pid == 0)
  	    {
                //call execvp
                if (execvp(command, argv) == -1)
		{
                    printf("\"%s\": command not found\n", command);

                    return -1;
                }
            }
            //parent process
            else
	    {
                wait(NULL); //waiting for child process to completed
            }
        }
        fflush(stdout);
    }

    return 0;
}
