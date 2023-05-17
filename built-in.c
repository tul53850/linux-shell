//Jason Hankins
//CIS 3207-001
//31-10-2022
//Project 2 shell implementation
//built-in.c

#include "myshell.h"

//testing purposes
//int main(int argc, char **argv, char **envp){
//    clr();
//    help();
//    return 0;
//}

int built_in_check(char **args, char **envp){
    //need to check if command is built in or not
        if(strcmp(args[0], "cd")==0){
            cd(args, envp);
            return 1;
        }
        if(strcmp(args[0], "clr")==0){
            clr();
            return 1;
        }
        if(strcmp(args[0], "dir")==0){
            dir(args, envp);
            return 1;
        }
        if(strcmp(args[0], "environ")==0){
            environ(args, envp);
            return 1;
        }
        if(strcmp(args[0], "echo")==0){
            echo(args);
            return 1;
        }
        if(strcmp(args[0], "help")==0){
            help();
            return 1;
        }
        if(strcmp(args[0], "pause")==0){
            pause2();
            return 1;
        }
        if(strcmp(args[0], "quit")==0){
            quit();
            exit(0);
            return 1;
        }
        return 0;
}

void cd(char **args, char **envp){
    if(chdir(args[1])!=0){ //if directory doesnt exist or no direcotry specified
        if(args[1]==NULL){
            char cwd[100];
            getcwd(cwd, sizeof(cwd));
            printf("CWD: %s\n", cwd);
        }
        else{
            printf("Error, directory could not be changed or %s does not exist\n", args[1]);
        }
    }
    else{
        chdir(args[1]);
        setenv("PWD", args[1], 1);
        //if directory does not exist print error
        //change PWD environment variable!!
    }
}

void clr(){
    printf("\e[1;1H\e[2J");
}

int dir(char **args, char **envp){
    DIR *d;
    struct dirent *dh;
    if(args[1] == NULL){
        char cwd[100];
        getcwd(cwd, sizeof(cwd));
        d = opendir(cwd);
    }
    //if directory does not exist print error
    else if((d = opendir(args[1])) == NULL){
        printf("error: dir could not open directory\n");
        return 1;
    }
    while((dh=readdir(d)) != NULL){
        printf("%s\n", dh->d_name);
    }
    closedir(d);
    return 0;
}

void environ(char **args, char **envp){
    //copy env command in the bash shell
    //char **envp is the list of environ variables
    //getenv(args);
    for(int i=0; envp[i]!=NULL; i++){
        printf("%s\n", envp[i]); //\n?
    }
    printf("\n");
}

//void path(){
//no longer necessary
//path environment variable still needs to be changed?
//}

void echo(char **args){
    for(int i=1; args[i]!=NULL; i++)
        printf("%s", args[i]);
    printf("\n");
}

void help(){
    //exec the more filter in bash...
    pid_t pid = fork();
    if(pid==0)
        execlp("more", "more", "readme_doc", NULL);
    waitpid(pid, NULL, 0);
}

void pause2(){
    char c;
    while(1){
        c=getc(stdin);
        if(c==13 || c==10)
            break;
    }
}

void quit(){
    exit(0);
}
