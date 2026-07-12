#include "ColorCoding.hpp"
#include <iostream>
#include <system_error>

FileType detectFileType(const std::filesystem::directory_entry& entry)
{
    std::error_code error;

    if (entry.is_symlink(error)) {
        return FileType::Symlink;
    }

    if (entry.is_directory(error)) {
        return FileType::Directory;
    }

    std::filesystem::perms p = entry.status(error).permissions();
    if ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none) {
        return FileType::Executable;
    }
    
    return FileType::Unknown;
}

std::string_view colorFor(FileType type)
{
    switch (type){
        case FileType::Directory:
        return Color::BLUE;

        case FileType::Symlink:
        return Color::CYAN;

        case FileType::Executable:
        return Color::GREEN;

        case FileType::Archive:
        return Color::RED;

        case FileType::Document:
        return Color::YELLOW;

        case FileType::Unknown:
        return Color::RESET;
    }
    return Color::RESET;
}

