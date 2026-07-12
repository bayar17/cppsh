#ifndef COLOR_CODING_HPP
#define COLOR_CODING_HPP

#include <iostream>
#include <filesystem>
#include <vector>
#include <string_view> // Added this just to be safe for std::string_view

namespace Color {
    inline constexpr std::string_view RESET = "\033[0m"; // Blank Color
    inline constexpr std::string_view RED   = "\033[31m"; // Archive
    inline constexpr std::string_view GREEN = "\033[32m"; // Executable
    inline constexpr std::string_view YELLOW = "\033[33m"; // Document
    inline constexpr std::string_view BLUE  = "\033[34m"; // Directory
    inline constexpr std::string_view CYAN  = "\033[36m"; // Symlinks
}

namespace fs = std::filesystem;

enum class FileType {
    Directory,
    Symlink,
    Executable,
    Archive,
    Document,
    Unknown
};

// 1. DECLARE THESE FIRST so the compiler knows they exist!
FileType detectFileType(const std::filesystem::directory_entry& entry);
std::string_view colorFor(FileType type);

// 2. NOW define listDirectory so it can use them
inline void listDirectory(const fs::path& directory)
{
    std::error_code error;

    fs::directory_iterator entries(directory, error);

    if (error) {
        std::cerr << "cppsh: ls: "
                  << error.message() << '\n';
        return;
    }

    for (const auto& entry : entries) {
        FileType type = detectFileType(entry);
        
        std::cout << colorFor(type) 
                  << entry.path().filename().string() 
                  << Color::RESET << '\n';
    }
}

#endif