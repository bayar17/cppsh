#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <cstdlib>

static bool executeCommand(const std::string& command) {
    if (command.empty()) {
        return true;
    }

    if (command == "exit") {
        return false;
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

        if (std::getline(std::cin, command)) 
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