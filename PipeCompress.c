#define _POSIX_SOURCE
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/* The Size of the data blocks copied in bytes */
#define BLOCK_SIZE 1024
/* Declare function to copy from one file handler to an other */
int16_t copy(int src, int dest, int pid);
int main(int argc, char const *argv[]) {
	/* looks for number of arguments and print manual */
	if(argc < 3) {
		printf("ERROR: Too few arguments. Usage: ./pipecopy src dest\n");
		return 3;
	}
	/* Create ordinary pipe */
	int fd[2];
	if (pipe(fd)) {
		fprintf (stderr, "ERROR: pipe creation failed.\n");
		return 1;
	}
	/* The fork process */
	pid_t children_1 = fork();
	pid_t children_2 = 0;
	/* Code for parent after forking child 1 */
	if(children_1 > 0) {
		/* Fork process again */
		children_2 = fork();
	}
	/* Code for child 1 (read file) */
	if(children_1 == 0) {
		/* Close read end of pipe */
		close(fd[0]);
		/* Open file pointer for source and handle error */
		int src = open(argv[1], O_RDONLY);
		if(src < 0) {
			printf("ERROR: Unable to open source file \"%s\" (%s)\n", argv[1], strerror(errno));	
			close(fd[1]);		
			return 1;
		}		
		/* Copy from file to pipe */
		if(copy(src, fd[1], 1) < 0) {
			printf("ERROR: error while copying: %s\n", strerror(errno));	
			close(src);
			close(fd[1]);
			return 2;
		}
		/* Close file and pipe */
		close(src);
		close(fd[1]);
		return 0;
	}
    	/* Code for parent after forking child 2 */
	if(children_2 > 0) {
		/* Close both ends of the pipe for parent */
		close(fd[0]);
		close(fd[1]);
		/* Wait for both childs to finish */
		bool error = false;
		for(uint8_t i=0; i<2; i++) {
			/* Wait for one child to terminate */
			int stat;
			pid_t done = wait(&stat);
			/* Query the plain exit status */
			stat = WEXITSTATUS(stat);
			/* Check which child is done */
			uint8_t children_number = 0;
			if(children_1 == done) {
				children_number = 1;
			} else {
				children_number = 2;
			}
			/* If the status is ok, print successull text */
			if(stat == 0) {
				printf("SUCCESS: Child %d finished normally.\n", children_number);
			} 
			/* If not, print error message and cancel other child */
			else {
				/* Print error */
				printf("ERROR: Child %d finished abnormally with stat %d\n", children_number, stat);
				/* Set error flag */
				error = true;
			}
		}
		/* Print message that all childs are terminated */
		if(!error) {
			printf("SUCCESS: All children are terminated normally.\n");
			return 0;
		} else {
			printf("ERROR: One or more child finished abnormally. Operation failed.\n");
			return 2;
		}
	}
	/* Code for child 2 (write file) */
	if(children_2 == 0) {
		/* Close write end of pipe */
		close(fd[1]);
		/* Open file pointer for destination and handle error */
		int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if(dest < 0) {
			printf("ERROR: Unable to open destination file \"%s\" (%s)\n", argv[2], strerror(errno));	
			close(fd[0]);
			return 1;
		}	
		/* Copy from pipe to file */
		if(copy(fd[0], dest, 2) < 0) {
			printf("ERROR: error while copying: %s\n", strerror(errno));	
			close(dest);
			close(fd[0]);
			return 2;
		}
		/* Close file and pipe */
		close(dest);
		close(fd[0]);
		return 0;
	}
	/* Code for error handling */
	if(children_1 < 0 || children_2 < 0) {
		printf("ERROR: Unable to for process!\n");
		/* If child 1 is already forked, we just let it finish normally */
		return 1;
	}
	return 0;
}
/* Copies the content from the source file handler to the dest file handler. */
int16_t copy(int src, int dest, int pid) {
	/* Create buffer and counter */
	uint8_t buffer[BLOCK_SIZE];
	int16_t read_count = 0;
	/* Copy blocks */
	while((read_count = read(src, buffer, BLOCK_SIZE)) > 0) {
		printf("[%d] %d bytes copied...\n", pid, read_count);
		write(dest, buffer, read_count);
	}
	return read_count;
}