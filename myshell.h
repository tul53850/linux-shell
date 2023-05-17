#ifndef MYSHELL_DOT_H
#define MYSHELL_DOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int parse(char * cmd, char** parsed);
void redirect(char **parsed, char **envp);
void execute(char **parsed, char **envp);
void execute_bg(char **parsed, char **envp);

int built_in_check(char **args, char **envp);
void cd(char **args, char **envp);
void clr();
int dir(char **args, char **envp);
void environ(char **args, char **envp);
void echo(char **args);
void help();
void pause2();
void quit();

void pipe_parsed(char **parsed, char **envp, int index);



#endif // MYSHELL_DOT_H
