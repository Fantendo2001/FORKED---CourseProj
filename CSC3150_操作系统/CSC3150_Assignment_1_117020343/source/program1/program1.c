#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){

	/* fork a child process */
    pid_t pid;
    int status;
    
    printf("Process start to fork\n");
    pid = fork();
    
    if (pid < 0) {
        printf("Fork error!\n");
    }
    else{
        
        // Child process
        if (pid == 0){
            printf("I'm the child process, my pid = %d\n", getpid());
            
            int i;
            char *arg[argc];
            for(i = 0; i < argc; i++) {
                arg[i] = argv[i+1];
            }
            arg[argc-1] = NULL;
            
            /* execute test program */
            printf("Child process start to execute the program\n");
            execve(arg[0], arg, NULL);
            
            // Check if the child process is replaced by new program
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
        // Parent process
        else{
            printf("I'm the parent process, my pid = %d\n", getpid());
            
            /* wait for child process terminates */
            waitpid(pid, &status, WUNTRACED);
            printf("Parent process receiving the SIGCHLD signal\n");
            
            /* check child process'  termination status */
            if (WIFEXITED(status)) {
                printf("Normal termination with EXIT STATUS = %d\n", WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)) {
                switch(WTERMSIG(status)){
                    case 1:
                        printf("child process get SIGHUP signal\nchild process is hang up by hang up signal\n"); break;
                    case 2:
                        printf("child process get SIGINT signal\nchild process is terminated because of terminal interrupt\n"); break;
                    case 3:
                        printf("child process get SIGQUIT signal\nchild process is terminated because of terminal quit\n"); break;
                    case 4:
                        printf("child process get SIGILL signal\nchild process is terminated because of illegal instruction\n"); break;
                    case 5:
                        printf("child process get SIGTRAP signal\nchild process is terminated because of trace trap\n"); break;
                    case 6:
                        printf("child process get SIGABRT signal\nchild process is abort by abort signal\n"); break;
                    case 7:
                        printf("child process get SIGBUS signal\nchild process is terminated because of bus error\n"); break;
                    case 8:
                        printf("child process get SIGFPE signal\nchild process is terminated because of floating point exception\n"); break;
                    case 9:
                        printf("child process get SIGKILL signal\n)child process is kill by kill signal\n"); break;
                    case 11:
                        printf("child process get SIGSEGV signal\nchild process is terminated because of invalid memory segment access\n"); break;
                    case 13:
                        printf("child process get SIGPIPE signal\nchild process is terminated because of writing on a pipe with no reader\n"); break;
                    case 14:
                        printf("child process get SIGALRM signal\nchild process is alarmed by alarm signal\n"); break;
                    case 15:
                        printf("child process get SIGTERM signal\nchild process is terminated by termination signal\n"); break;
                }
                printf("CHILD EXECUTION FAILED!!\n");
            }else if(WIFSTOPPED(status)) {
                printf("child process get SIGSTOP signal\nchild process stopped\n");
                printf("CHILD PROCESS STOPPED\n");
            }else{
                printf("CHILD PROCESS CONTINUED\n");
            }
            exit(0);
        }
        
    }
}
