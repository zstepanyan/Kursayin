#include "VirtualFileSystem.h"
#include <iostream>
#include <sstream>
#include <algorithm>

VirtualFileSystem::VirtualFileSystem() {
    root = new Directory();
    cwd = root;
    cwdPath = "/";
}

VirtualFileSystem::~VirtualFileSystem() {
    delete root;
}

std::string VirtualFileSystem::pwd() {
    return cwdPath;
}

std::string VirtualFileSystem::touch(const std::string& filename) {
    if (cwd->subdirs.find(filename) != cwd->subdirs.end()) {
        return "Error: " + filename + " already exists.";
    }
    cwd->subdirs[filename] = nullptr;
    return "File '" + filename + "' created.";
}

std::string VirtualFileSystem::mkdir(const std::string& dirname) {
    if (cwd->subdirs.find(dirname) != cwd->subdirs.end()) {
        return "Error: Directory '" + dirname + "' already exists.";
    }
    cwd->subdirs[dirname] = new Directory();
    return "Directory '" + dirname + "' created.";
}

std::string VirtualFileSystem::cd(const std::string& path) {
    if (path == "/") {
        cwd = root;
        cwdPath = "/";
        return "Changed directory to root";
    }

    std::vector<std::string> parts;
    std::string currentPart;
    std::stringstream ss(path);
    while (getline(ss, currentPart, '/')) {
        if (!currentPart.empty()) {
            parts.push_back(currentPart);
        }
    }

    Directory* tempDir = (path[0] == '/') ? root : cwd;
    for (const std::string& part : parts) {
        if (tempDir->subdirs.find(part) != tempDir->subdirs.end()) {
            tempDir = tempDir->subdirs[part];
            cwdPath += "/" + part;
        } 
        else {
            return "Error: Directory '" + part + "' not found.";
        }
    }

    cwd = tempDir;
    return "Changed directory to " + cwdPath;
}

std::string VirtualFileSystem::rm(const std::string& filename) {
    auto it = cwd->subdirs.find(filename);
    if (it != cwd->subdirs.end()) {
        delete it->second;
        cwd->subdirs.erase(it);
        return "File or directory '" + filename + "' removed.";
    }
    return "Error: File or directory '" + filename + "' not found.";
}

std::string VirtualFileSystem::ls(bool showAll) {
    std::string result;
    for (const auto& item : cwd->subdirs) {
        if (item.first != "..") {
            if (!showAll && item.first[0] == '.') continue;
            result += item.first + "\n";
        }
    }
    return result.empty() ? "No items found." : result;
}

std::string VirtualFileSystem::ll() {
    std::string result;
    for (const auto& item : cwd->subdirs) {
        result += (item.second == nullptr ? "[FILE] " : "[DIR] ") + item.first + "\n";
    }
    return result.empty() ? "No items found." : result;
}

std::string VirtualFileSystem::cp(const std::string& src, const std::string& dest) {
    auto srcDir = cwd->subdirs.find(src);
    if (srcDir == cwd->subdirs.end()) {
        return "Error: Source file or directory '" + src + "' not found.";
    }

    if (cwd->subdirs.find(dest) != cwd->subdirs.end()) {
        return "Error: Destination file or directory '" + dest + "' already exists.";
    }

    cwd->subdirs[dest] = srcDir->second;
    return "Copied '" + src + "' to '" + dest + "'";
}

std::string VirtualFileSystem::mv(const std::string& src, const std::string& dest) {
    auto srcDir = cwd->subdirs.find(src);
    if (srcDir == cwd->subdirs.end()) {
        return "Error: Source file or directory '" + src + "' not found.";
    }

    if (cwd->subdirs.find(dest) != cwd->subdirs.end()) {
        return "Error: Destination file or directory '" + dest + "' already exists.";
    }

    cwd->subdirs[dest] = srcDir->second;
    cwd->subdirs.erase(src);
    return "Moved '" + src + "' to '" + dest + "'";
}

std::string VirtualFileSystem::show_tree() {
    std::string tree;
    build_tree(root, 0, tree);
    return tree;
}

void VirtualFileSystem::build_tree(Directory* dir, int depth, std::string& tree) {
    for (const auto& item : dir->subdirs) {
        tree += std::string(depth * 2, ' ');
        if (item.second == nullptr) {
            tree += item.first + "\n";
        } else {
            tree += "[DIR] " + item.first + "\n";
            build_tree(item.second, depth + 1, tree);
        }
    }
}

std::string VirtualFileSystem::find(const std::string& query) {
    std::string result = search_recursively(root, query, cwdPath);
    return result.empty() ? "No matches found." : result;
}

std::string VirtualFileSystem::search_recursively(Directory* dir, const std::string& query, const std::string& currentPath) {
    std::string result;
    for (const auto& item : dir->subdirs) {
        std::string fullPath = currentPath + "/" + item.first;
        if (item.first.find(query) != std::string::npos) {
            result += fullPath + "\n";
        }
        if (item.second != nullptr) {
            result += search_recursively(item.second, query, fullPath);
        }
    }
    return result;
}
