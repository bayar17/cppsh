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

    const int status = std::system(command.c_str());

    std::string mutedCommand = command + " 2> /dev/null"; 

    int statusCode = std::system(mutedCommand.c_str());

    if (statusCode != 0) {
        std::cout << "cppsh: command failed\n";
    }
}

static void mainShell() {
    std::string dummy;
    do {
        std::cout << "$ " << std::flush; 

        if (std::getline(std::cin, dummy)) {
            executeCommand(dummy); 
        } else {
            break; 
        }
    } while (true);

    if (!executeCommand(command)) {
            break;
    }
}

#endif // SHELL_H