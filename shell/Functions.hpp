#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <filesystem>

namespace fs = std::filesystem;

static bool executeCommand(const std::string& command) {
    if (command.empty()) {
        return true;
    }

    std::vector<std::string> args_str;
    std::istringstream iss(command);
    std::string arg;
    while (iss >> arg) {
        args_str.push_back(arg);
    }

    if (args_str.empty()) return true;

    
    if (args_str[0] == "exit") {
        return false;
    }

    if (args_str[0] == "cd") {
        if (args_str.size() > 1) {
            std::error_code ec;
            fs::current_path(args_str[1], ec);
            if (ec) {
                std::cout << "cppsh: cd: " << args_str[1] << ": " << ec.message() << '\n';
            }
        } else {
            const char* home = std::getenv("HOME");
            if (home) {
                std::error_code ec;
                fs::current_path(home, ec);
            }
        }
        return true;
    }

    if (args_str[0] == "ls") {
        args_str.push_back("-G"); 
    }

    std::vector<char*> args_c;
    for (auto& s : args_str) {
        args_c.push_back(const_cast<char*>(s.c_str()));
    }
    args_c.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "cppsh: fork failed\n";
    } 
    else if (pid == 0) {
        if (execvp(args_c[0], args_c.data()) == -1) {
            std::cerr << "cppsh: command not found: " << args_c[0] << '\n';
        }
        exit(EXIT_FAILURE); 
    } 
    else {
        int status;
        waitpid(pid, &status, 0);
    }

    return true;
}

static void mainShell() {
    std::string command;

    while (true) {
        std::cout << "$ " << std::flush; 

        if (!std::getline(std::cin, command)) 
        {
            break;
        }
        if (!executeCommand(command)) 
        {
            break;
        }
    } 
}

#endif // SHELL_H