#ifndef VIRTUAL_FILE_SYSTEM_H
#define VIRTUAL_FILE_SYSTEM_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>

class VirtualFileSystem {
public:
    VirtualFileSystem();
    ~VirtualFileSystem();

    std::string pwd();
    std::string touch(const std::string& filename);
    std::string mkdir(const std::string& dirname);
    std::string cd(const std::string& path);
    std::string rm(const std::string& filename);
    std::string ls(bool showAll = false);
    std::string ll();
    std::string cp(const std::string& src, const std::string& dest);
    std::string mv(const std::string& src, const std::string& dest);
    std::string show_tree();
    std::string find(const std::string& query);

private:
    struct Directory {
        std::map<std::string, Directory*> subdirs;
        bool isFile = false;
    };

    Directory* root;
    Directory* cwd;
    std::string cwdPath;

    void build_tree(Directory* dir, int depth, std::string& tree);
    std::string search_recursively(Directory* dir, const std::string& query, const std::string& currentPath);

};

#endif  // VIRTUAL_FILE_SYSTEM_H
