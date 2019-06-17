#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sys/wait.h>
#include <csignal>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <ctime>
#include <sstream>
#define asyncFlag "&"
#define changeDirCommand "cd"
#define BUFSIZE 512

using namespace std;
ofstream logStream;
 
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
 
void logTime() {
    if(logStream.is_open()) {
        time_t now;
        now = time(0);
        string currentTime = ctime(&now);
        logStream << '[';
        logStream << currentTime.substr(0, currentTime.size() - 1);
        logStream << ']';
    }
}
 
void logCommand(vector<string> arguments, bool execAsync) {
    if(logStream.is_open()) {
        for(string s : arguments) {
            logStream << " ";
            logStream << s;
        }
        if(execAsync) {
            logStream << " &";
        }
        logStream << "\n";
    }
}
 
void stopLog() {
    if(logStream.is_open()) {
        logStream.close();
    }
}
 
int main() {
    pid_t childPid = -1;
 
    bool once = true;
    int status;
    char command[20], *parameters[60];
    pid_t bgPid;
    int n;
    char buf[BUFSIZE];
    time_t t;
    time(&t);
 
    logStream.open("log");
 
 
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
                logTime();
                logCommand(arguments, execAsync);
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
 
 
 
    stopLog();
    return 0;
}
