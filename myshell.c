//Jason Hankins
//CIS 3207-001
//31-10-2022
//Project 2 shell implementation
//myshell.c

#include "myshell.h"

int main(int argc, char **argv, char **envp){
    FILE *in;
    int batch = 0; //True or false if batch
    if(argc==1) //including myshell command itself at [0]!
        in = stdin;
    else if(argc==2){
        //open batch file in argument
        if((in = fopen(argv[1], "r")) == NULL){
            perror("batch file could not be opened");
            exit(1);
        }
        batch = 1;
    }
    else{
        perror("Too many arguments");
        exit(1);
    }

    //i. The shell environment should contain
    //shell=<pathname>/myshell where <pathname>/myshell
    //is the full path for the shell executable
    //(not a hardwired path back to your directory,
    //but the one from which it was executed). ????
    char shell[1024];
    strcpy(shell, getenv("PWD"));
    strcat(shell, "/myshell");
    setenv("SHELL", shell, 1); //1 overwrite, 0 does nothing if present

    printf("\n myshell initialized \n\n");
    //clear screen?

    char *cmd = NULL;
    char **parsed;
    size_t size;
    int args=0; //number of args so the array of strings can allocate memory.
    int bg;
    int pipe;
    int b_stdout = dup(STDOUT_FILENO);
    int b_stdin = dup(STDIN_FILENO);
    while(1){
        //prompts user if interactive
        //waitpid(-1,NULL,WNOHANG);
        if(batch == 0)
            printf("myshell> ");

        getline(&cmd, &size, in); //read commandline / batch
        if(feof(in))
            exit(0); //finished batch commands

        if(size==0) //just for debugging now
            break;


        bg=0;
        if(strchr(cmd, '&'))
            bg=1;
        pipe=0;
        if(strchr(cmd, '|'))
            pipe=1;


        parsed = malloc(1024*sizeof(char*)); //how to know size?
        args=parse(cmd, parsed); //args returned so free() knows how many to deallocate
        free(cmd);
        cmd = NULL;

        redirect(parsed, envp);

        if(bg==0 && pipe==0) //background execution is handled in redirect function
            execute(parsed, envp);

        for(int i=0; i<args; i++){
            free(parsed[i]); //use FREE? (keep getting garbage values)
            parsed[i] == NULL;
        }
        free(parsed);
        parsed = NULL;
        fflush(stdout);
        fflush(stdin);
        dup2(b_stdout, STDOUT_FILENO);
        dup2(b_stdin, STDIN_FILENO);
    }
    return 0;
}
