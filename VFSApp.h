#ifndef VFS_APP_H
#define VFS_APP_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "VirtualFileSystem.h"

class User {
public:
    std::string username;
    bool isAdmin;

    User(const std::string& user, bool admin = false) : username(user), isAdmin(admin) {}
};

class VFSApp {
private:
    VirtualFileSystem vfs;
    std::unique_ptr<User> currentUser;

    void execute_command(const std::string& command);
    void execute_command_without_sudo(const std::vector<std::string>& parts);
    void show_help(const std::string& cmd = "");
    void show_about();

public:
    VFSApp();
    void setUser(const std::string& username, bool isAdmin);
    void run();
};

#endif  // VFS_APP_H
