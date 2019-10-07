#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

int main (int argc, char* argv[]) {
    char* fileName;
    char* outputFileName;
    pid_t pid;
    pid = fork();

    // argc is 3
    if (argc == 3) {
        fileName = argv[1];
        outputFileName = argv[2];
    }
    else {
        cout << stderr << "Specify infilename then outfilename as command line arguments\n";
    }

    // if pid less than 0 or fork fails
    if (pid < 0) {
        cout << stderr << "Fork failed. Program exit\n";
    }
    
    // child proc
    else if (pid == 0) {
        cout << "Starting child compression\n";

        //Execute line command usage to compress
		execl("./myCompress", "./myCompress",  fileName, outputFileName, NULL);
	}
    
    // parent process
    else {
        cout << "Parent waitng to compress\n";
        wait(NULL);
        cout << "Waiting complete\n";
    }
    return 0;
}