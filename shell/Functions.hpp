#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <cstdlib> // Needed for std::system()

static void executeCommand(const std::string& command) {
    if (command.empty()) {
        return;
    }

    // 1. Mute the default shell error by redirecting stderr (2>) to the system's trash bin
    // On Mac/Linux: 2> /dev/null
    // On Windows: 2> nul
    std::string mutedCommand = command + " 2> /dev/null"; 

    // 2. Run the muted command
    int statusCode = std::system(mutedCommand.c_str());

    // 3. If the status code is non-zero, the command failed
    if (statusCode != 0) {
        std::cout << "cppsh: Command failed to execute.\n";
    }
}

static void mainShell() {
    std::string dummy;
    do {
        std::cout << "$ " << std::flush; 
        
        // Grab the input line
        if (std::getline(std::cin, dummy)) {
            // Send the input to your execute function!
            executeCommand(dummy); 
        } else {
            break; 
        }
    } while (true);
}

#endif // SHELL_H