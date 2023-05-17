# Project-2-F22: shell implementation

Jason Hankins
CIS 3207-001
10-31-2022

**The full Project 2 description is [here](https://github.com/CIS-3207-F22/project-2-linux-shell-tul53850/blob/main/Project%202%20Developing%20a%20Linux%20Shell.pdf)**.   

# Overview
This purpose of this project is to build a simple Unix/Linux shell. When you type in a command, the shell creates a child process that executes the command you entered and then prompts for more user input when it has finished.  

### Basic Shell 'myshell': 

The myshell program operates on a loop: it repeatedly prints a prompt myshell> , parses the input, executes the command specified on that line of input, and waits for the command to finish.
The shell can be invoked in /interactive/ mode, and allows the user to type commands directly. The shell also supports a /batch mode/, which instead reads input from a batch file and executes commands found in the file.
The shell can execute any commands in the environment path.

myshell also contains the following commands:  
a. cd <directory> - Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory.
b. clr - Clear the screen.  
c. dir <directory> - List the contents of directory <directory>.  
d. environ - List all the environment strings.  
e. echo <comment> - Display  <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).  
f. help - Display the user manual using the more filter.   
g. pause - Pause operation of the shell until ‘Enter’ is pressed.  
h. quit - Quit the shell.
  
 
 # I/O FEATURES
  
 a. '<' Redirects stdin to be from the argument to the right. 
   
 b. '>' Redirects stdout to be from the argument to the right. Creates if it does not exist, otherwise overwrites.  
  
 c. ">" Redirects stdout to be from the argument to the right. Creates if it does not exist, otherwise appends. 
  
 d. '&' Declares program to be executed to run in the background. Multiple can run in the background at once. 
  
 e. '|' Command line pipes that connect output from one program to the input of another.  
  
 
 Example:
   programname arg1 arg2 < inputfile > outputfile
will execute the program /programname/ with arguments /arg1/ and /arg2/, the stdin FILE stream replaced by /inputfile/ and the stdout FILE stream replaced by /outputfile/. 

# Testing
To test my program, I used the cis-linux server. I began with my pseudocode and started to implement the built-in commands. To test this, I added a main() to my built-in file and tested various entries to debug and fix any issues with it.  
The next part I implemented was the main myshell.c file. The main feature of this file is the while(1) loop, which is the controller for the entire program. I added empty functions for things I wanted to implement later, like redirect(args, envp) and execute(args, envp) so I could test my parser. 
The parsing was what I had the most difficulty with, as it was hard to figure out what the size of the array was going to be beforehand. I use malloc() and free() in each loop to allocate space for the commands each time the loop runs. 
I then added an execution function for programs that weren't built-in. I make use of fork() and execvp() to fork a child and check the path environment variable for programs to run. 
The file redirection ended u being almost the same as my pseudocode and was implemented very quickly. 
The most difficulty I had was with pipes and background execution. This was implemented last. 
