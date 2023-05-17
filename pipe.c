//Jason Hankins
//CIS 3207-001
//31-10-2022
//Project 2 shell implementation
//pipe.c

#include "myshell.h"

void pipe_parsed(char **parsed, char **envp, int index){
    char **dst = &parsed[index+1]; //begins at right side of parsed
    pid_t pid;
    pid_t pid2;
    //file descriptor one to read and one to send
    int filedes[2]; //pipe takes  int array of src and dst
    //create pipe before fork!!
    //if return -1 then error else fork
    if(pipe(filedes)==-1){
        printf("Pipe error\n");
        exit(1);
    }
    pid = fork();
    if(pid<0)
        printf("Fork Error pid\n");
    else if(pid==0){
        close(STDOUT_FILENO); //close stdout?

        dup2(filedes[1], STDOUT_FILENO); //1

        close(filedes[0]);

        //runs in background regardless
        parsed[index]==NULL; //Nullifies '|' character
        execute_bg(parsed, envp); //everything before '|'

        close(filedes[1]);
        //redirect(parsed, envp); NOT REQUIRED
        exit(0);
    }

    //else FORK AGAIN,,, below, new pid variable??
    else{
        pid2 = fork();
        if(pid2<0)
            printf("Fork Error pid2\n");
        else if(pid2==0){
            close(STDIN_FILENO); //close stdin?

            dup2(filedes[0], STDIN_FILENO); //replace stdin '0' w reading end of pipe

            close(filedes[1]);

            //check if run in bg?
            int bg = 0;
            for(int i=0; dst[i]!=NULL; i++){
                if(strchr(dst[i], '&'))
                    bg = 1;
            }
            if(bg==1)
                execute_bg(dst, envp); //execute right side of parsed
            else
                execute(dst, envp);
            close(filedes[0]);
            //redirect(dst, envp); NOT REQUIRED
            exit(0);
        }

        //else wait(&pid)??? from parent waiting until children done
        else{
            close(filedes[1]);
            close(filedes[0]);
            int waitstat;
            waitpid(pid, &waitstat, WNOHANG);
            waitpid(pid2, &waitstat, WNOHANG);
        }
    }
}
