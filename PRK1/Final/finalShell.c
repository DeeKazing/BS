#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sstream>
/*
Zeichen 	Umwandlung
%d oder %i 	int
%c 		einzelnes Zeichen
%e oder %E 	double im Format [-]d.ddd e±dd bzw. [-]d.ddd E±dd
%f 		double im Format [-]ddd.ddd
%o 		int als Oktalzahl ausgeben
%p 		die Adresse eines Zeigers
%s 		Zeichenkette ausgeben
%u 		unsigned int
%x oder %X 	int als Hexadezimalzahl ausgeben
%% 		Prozentzeichen 
*/
#define BUFSIZE 512
using namespace std;
int DATAPATH(char *path) {		//methode for reading datapath
    return chdir(path);			//change working directory
}
void read_cmd(char *com, char **para) {	//read cmd in for output and logfile
    for (int i = 0; i < 100; ++i) {	
        para[i] = strsep(&com, " ");	//extract token from string and put in para[i]
        if (para[i] == NULL || para[i] == "") break; //if nothing in para[i] start in a new "command"
    }
    return;
}
void verlassen(int v) {				//methode zum verlasen der mini shell
    cout << endl << "Do you really want to quit(y/n)?";
    char YESNO = getchar(); 			//read and put it in YESNO
    if (YESNO == 'y' || YESNO == 'Y') {		//check If user writes Y
        exit(0);
    }else{ 
	cout << "Ok, continue!"<< endl;		//if not continue
    return;
}
}
int main() {
    pid_t bgPid, childPid = -1;
    char cmd[20], *parameters[60];
    bool einmalig = true; //für die eingabe CTR-C
    int status, n;
    char buffer[BUFSIZE];
    time_t aktuellezeit;
    time(&aktuellezeit);
    FILE *f = fopen("test.log", "write");
    while (1) {
        bool temp = false;
        if (einmalig) {
            cout << "exit with CTR-C" << endl;
            einmalig = false;
        }
        char cwd[1024];
        getcwd(cwd, sizeof (cwd));
        signal(SIGINT, verlassen); //Overview of signals
        printf("%s", cwd); printf(" > ");   //print string of characters

        fgets(cmd, sizeof (cmd), stdin);
        fprintf(f, "%s", ctime(&aktuellezeit)); fprintf(f, "\t"); fprintf(f, "%s", cmd); fprintf(f, "\n");
        //calculate lenth of a string (split the cmd)
 	if (cmd[strlen(cmd) - 1] == '\n') { //
            cmd[strlen(cmd) - 1] = '\0';
        }
        if (cmd[strlen(cmd) - 1] == '&') {
            cmd[strlen(cmd) - 1] = '\0';
            cmd[strlen(cmd) - 1] = '\0';
            temp = true;
        }
        read_cmd(cmd, parameters);
        if (strcmp(parameters[0], "cd") == 0) { //compare 2 strings
            if (DATAPATH(parameters[1]) < 0) {
                perror(parameters[1]);
            }
        }
/*Fork system call use for creates a new process, which is called child process, which runs concurrently with process (which process called system call fork) and this process is called parent process. After a new child process created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.

It takes no parameters and returns an integer value. Below are different values returned by fork().

Negative Value: creation of a child process was unsuccessful.
Zero: Returned to the newly created child process.
Positive value: Returned to parent or caller. The value contains process ID of newly created child process.*/
        if ((childPid = fork()) == -1) {
            fprintf(stderr, "cant fork");
            exit(1);
        } else if (childPid == 0) {
            execvp(cmd, parameters);		//execute a file
	    cerr << "Could not execute " << cmd << endl;
            exit(0);
                    } else {
                waitpid(childPid, 0, 0); //wait for a child process to stop or terminate
//pid_t waitpid(pid_t pid, int *stat_loc, int options);
            }
        }
    return 0;
}
