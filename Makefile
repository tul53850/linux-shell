# Jason Hankins
# 3207-001
# 10-31-2022
# project 2: myshell

CC = gcc
C = -Wall -Werror

default:myshell

myshell: myshell.o parse_redirect_exec.o pipe.o built-in.o
	$(CC) $(CFLAGS) -o myshell myshell.o parse_redirect_exec.o pipe.o built-in.o $(C)

myshell.o: myshell.c
	$(CC) $(CFLAGS) -c myshell.c

parse_redirect_exec.o: parse_redirect_exec.c
	$(CC) $(CFLAGS) -c parse_redirect_exec.c

pipe.o: pipe.c
	$(CC) $(CFLAGS) -c pipe.c

built-in.o: built-in.c
	$(CC) $(CFLAGS) -c built-in.c

clean:
	$(RM) myshell *.o *~
 
