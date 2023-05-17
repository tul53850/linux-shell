//Jason Hankins
//CIS 3207-001
//31-10-2022
//Project 2 shell implementation
//parse_redirect_exec.c

#include "myshell.h"

int parse(char *cmd, char **parsed){
    char *tk = strtok(cmd, " \n\t");
    int i = 0;
    while(tk != NULL){
        parsed[i] = malloc(strlen(tk)*sizeof(char)); //should do calloc instead? instead of 128 should it be strlen(tk);?
        strcpy(parsed[i], tk);
        //printf("void parse: %d, %s\n", i, parsed[i]);
        tk = strtok(NULL, " \n\t");
        i++;
    }
    parsed[i]==NULL;
    return i;
}

void redirect(char **parsed, char **envp){
    char *file;
    int fd;
    int bg = 0;
    for(int i=0; parsed[i]!=NULL; i++){
        //redirect input
        if(strchr(parsed[i], '<')){
            file=parsed[i+1];
            fd = open(file, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            parsed[i] = NULL; // command1 (<)NULL in 2
        }
        //redirect output (used mainly to send output to a file instead of screen.)
        else if(strchr(parsed[i], '>') || strstr(parsed[i], ">>")){
            file=parsed[i+1];
            if(strchr(parsed[i], '>'))
                fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
            else
                fd = open(file, O_WRONLY | O_CREAT | O_APPEND); //concat >>
            dup2(fd, STDOUT_FILENO);
            parsed[i] = NULL; // command1 (>)NULL out 2
        }

        //background

        else if(strchr(parsed[i], '&')){
            parsed[i]==NULL;
            execute_bg(parsed, envp);
            parsed=&parsed[i]; //move it to begin after instead to check for more?
        }
        //pipe
        //does not need to handle pipe & redirect at same time!
        else if(strchr(parsed[i], '|')){
            pipe_parsed(parsed, envp, i);
            break;
        }
    }
    close(fd);
}

void execute(char **parsed, char **envp){
    pid_t pid;

    printf("command: %s\n args: ", parsed[0]);
    for(int i=1; parsed[i]!=NULL; i++)
        printf("[%s] ", parsed[i]);
    printf("\n");

    if(built_in_check(parsed, envp)==0){ //that is, not a built in...
        pid = fork();
        if(pid<0)
            printf("Fork Error pid (exe)\n");
        else if(pid == 0){
            //access(); to see if a file exists in a directory and is executable
            setenv("PARENT", getenv("SHELL"), 1);
            if(execvp(parsed[0], parsed)==-1){
                printf("Error: %s failed to run\n", parsed[0]);
                exit(1);
            }
        }
        else
            waitpid(pid, NULL, 0);
    }
}

void execute_bg(char **parsed, char **envp){
    if(built_in_check(parsed, envp)==0){ //that is, not a built in...
        setenv("PARENT", getenv("SHELL"), 1);
        if(execvp(parsed[0], parsed)==-1){
            printf("Error: %s failed to run\n", parsed[0]);
            exit(1);
        }
    }
}
