#include "shell/Functions.hpp"
#include <string>
#include <iostream>
#include <sys/utsname.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string first_arg = argv[1];
        if (first_arg == "--version") {
            struct utsname sys_info;
            if (uname(&sys_info) == 0){
                std::cout << "cppsh, version " << CPPSH_VERSION << " (" << MACHTYPE << ")\n";
                return 0;
            }
        }
    }
    mainShell();
    return 0;
}