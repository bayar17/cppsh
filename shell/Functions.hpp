#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include "ColorCoding.hpp"

static bool executeCommand(const std::string& command) {
    if (command.empty()) {
        return true;
    }

    if (command == "exit") {
        return false;
    }

    if (command == "ls") {
        listDirectory(fs::current_path());
        return true;
    }

    if (command.substr(0, 3) == "cd ") {
        std::string path = command.substr(3);
        std::error_code ec;

        fs::current_path(path, ec);

        if (ec) {
            std::cout << "cppsh: cd: " << path << ": " << ec.message() << '\n';
        }
        return true;
    } else if (command == "cd") {
        const char* home = std::getenv("HOME");
        if (home) {
            std::error_code ec;
            fs::current_path(home, ec);
        }
        return true;
    }

    std::string mutedCommand = command + " 2> /dev/null"; 

    int statusCode = std::system(mutedCommand.c_str());

    if (statusCode != 0) {
        std::cout << "cppsh: command failed\n";
        return true;
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