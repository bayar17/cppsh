#ifndef COLOR_CODING_HPP
#define COLOR_CODING_HPP

#include <iostream>
#include <filesystem>
#include <vector>


namespace Color {
    inline constexpr std::string_view RESET = "\033[0m"; // Blank Color
    inline constexpr std::string_view RED   = "\033[31m"; // Archive (Example: *.tar, *.tar.gz, *.zip, *.rar, *.iso, based on it's magic number)
    inline constexpr std::string_view GREEN = "\033[32m"; // Executable
    inline constexpr std::string_view YELLOW = "\033[33m"; // Document (Example: *.txt, *.docx, *.json, based on it's magic number)
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
        std::cout << entry.path().filename().string() << '\n';
    }
}

FileType detectFileType(const std::filesystem::directory_entry& entry);

#endif


