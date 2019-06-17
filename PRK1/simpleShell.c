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

string getPath() {
    char pathBuffer[60];
    getcwd(pathBuffer, 60);
    string pathString(pathBuffer);
    return pathString;
}

vector<string> readCommand() {
	string input = "";
	vector<string> parsedArgs;
	stringstream arg;
	getline(cin, input);
        if(input.size() > 0) {
            for(char c : input) {
                if(c != ' ') {
                    arg << c;
                } else {
                    parsedArgs.push_back(arg.str());
                    arg.str("");
                }
            }
            parsedArgs.push_back(arg.str());
        }
	return parsedArgs;
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

void handler(int signal) {
    switch(signal) {
        case SIGINT: {
            cout << endl << "Do you really want to quit this masterful console? (y/n)";
            string query;
            cin >> query;
            if(query == "y" || query == "Y") {
                stopLog();
                exit(3);
            }
            break;
        }
        case SIGCHLD: {
            pid_t pid = wait(NULL);
            if(pid == -1) {
                cout << "could not wait on child" << endl;
            }
            break;
        }
    }
    return;
}

int main() {
    signal(SIGCHLD, handler);
    signal(SIGINT, handler);
    logStream.open("log");
    while (true) {
        bool execAsync = false;
        pid_t childPid;
        cout << getPath() << " > ";
        vector<string> arguments = readCommand();

        if(arguments.size() > 0) {

            //check if command should be executed asynchronously
            if(execAsync = (arguments.back() == asyncFlag)) {
                arguments.pop_back();
            }
            //check if command is to change working directory
            if(arguments.front() == changeDirCommand) {
                chdir(arguments[1].c_str());
            }

            //convert string vector to cstring array
            char **carguments = (char**)malloc((arguments.size()+1)*sizeof(char*));
            for(int i = 0; i < arguments.size(); i++){
                carguments[i] = new char[arguments[i].size() + 1];
                strcpy(carguments[i], arguments[i].c_str());
            }
            carguments[arguments.size()] = NULL;

            //fork
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

