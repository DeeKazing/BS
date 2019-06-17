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
using namespace std;
ofstream logStream;

string getDataPfad() {
    char path[60];
    getcwd(path, 60);
    string pathString(path);
    return pathString;
}
 
void read_command(char *com, char **para) {
 
    for (int i = 0; i < 60; ++i) {
 
        para[i] = strsep(&com, " ");
 
        if (para[i] == NULL || para[i] == "") break;
 
    }
 
    return;
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
 
void quitCtr_C(int sig) {
    printf("\nDo you really want to quit(y/n)?");
    char YESNO;
    YESNO = getchar();
    if (YESNO == 'y') {
        exit(0);
    }
}
int main(){
    bool once =true;
    logStream.open("log");
     while (true) {
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
       
        pid_t childPid;
        cout << getDataPfad() << " > ";
   
    read_command(command, parameters);
        if (strcmp(parameters[0], "cd") == 0) {
            if (cd(parameters[1]) < 0) {
                perror(parameters[1]);
            }
        }
     }
 
            childPid = fork();
            pid_t realPid = getpid();
            if(childPid  == -1) {
                cerr << "can't fork" << endl;
            } else if (childPid == 0) { //child process
                if(execAsync) {
                    cout << '[' << realPid << ']' << endl;
                }
                execvp(carguments[0], carguments);
                exit(3);
            } else { //parent process
                logTime();
                logCommand(arguments, execAsync);
                if(!execAsync) {
                    pause();
                }
            }
            delete [] carguments;
        }
    }
    stopLog();
    return 0;
}
