#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class File {
public:
    std::string name;
    std::string content;

    File(const std::string& name) : name(name) {}
};

class Directory {
public:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<Directory>> directories;
    std::unordered_map<std::string, std::shared_ptr<File>> files;

    Directory(const std::string& name) : name(name) {}

    void listContents() const {
        for (const auto& [name, dir] : directories) {
            std::cout << "Dir: " << name << std::endl;
        }
        for (const auto& [name, file] : files) {
            std::cout << "File: " << name << std::endl;
        }
    }
};

class FileSystem {
    std::shared_ptr<Directory> root;
public:
    FileSystem() : root(std::make_shared<Directory>("root")) {}

    void mkdir(const std::string& dirName) {
        root->directories[dirName] = std::make_shared<Directory>(dirName);
        std::cout << "Directory created: " << dirName << std::endl;
    }

    void ls() const {
        root->listContents();
    }
};


#endif // FILESYSTEM_H