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
#define BUFSIZE 512
 
using namespace std;
 
void read_command(char *com, char **para) {
 
    for (int i = 0; i < 60; ++i) {
 
        para[i] = strsep(&com, " ");
 
        if (para[i] == NULL || para[i] == "") break;
 
    }
 
    return;
}
 
void quitCtr_C(int sig) {
    printf("\nDo you want to quit(y/n)?");
 
    char s;
    s = getchar();
    if (s == 'y') {
        exit(0);
    }
 
    return;
}
 
int cd(char *path) {
    return chdir(path);
}
 
int main() {
    pid_t childPid = -1;
 
    bool once = true;
    int status;
    char command[20];
    char *parameters[60];
    pid_t bgPid;
    int n;
    char buf[BUFSIZE];
    time_t t;
    time(&t);
 
    FILE *f;
    f = fopen("test.log", "w");
 
 
    while (1) {
        bool bg = false;
 
 
        if (once) {
            cout << "exit with CTR-C" << endl;
            once = false;
        }
 
        char cwd[1024];
 
        getcwd(cwd, sizeof (cwd));
 
        signal(SIGINT, quitCtr_C);
 
 
        printf("%s", cwd);
        printf(" > ");
 
        fgets(command, sizeof (command), stdin);
        fprintf(f, "%s", ctime(&t));
        fprintf(f, "\t");
        fprintf(f, "%s", command);
        fprintf(f, "\n");
 
 
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }
 
        if (command[strlen(command) - 1] == '&') {
            command[strlen(command) - 1] = '\0';
            command[strlen(command) - 1] = '\0';
            bg = true;
 
        }
 
 
        read_command(command, parameters);
 
 
        if (strcmp(parameters[0], "cd") == 0) {
            if (cd(parameters[1]) < 0) {
                perror(parameters[1]);
            }
        }
 
 
        if ((childPid = fork()) == -1) {
            fprintf(stderr, "cant fork");
            exit(1);
        } else if (childPid == 0) {
            //fprintf(stderr, "child process\n");
            execvp(command, parameters);
            exit(0);
        } else {
 
            if (bg) {
               
                signal(SIGCHLD, SIG_IGN);
                printf("[");
                printf("%d", childPid);
                printf("]\n");
 
 
                //bg = false;
            } else {
 
                waitpid(childPid, 0, 0);
 
            }
        }
 
 
    }
 
 
 
 
    return 0;
}
