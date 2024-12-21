#include "VFSApp.h"

VFSApp::VFSApp() {
    currentUser = std::make_unique<User>("guest");
}

void VFSApp::setUser(const std::string& username, bool isAdmin) {
    currentUser = std::make_unique<User>(username, isAdmin);
    std::cout << "User set to: " << username << std::endl;
}

void VFSApp::run() {
    std::string command;
    std::cout << "Welcome to the Virtual File System!" << std::endl;
    std::cout << "Current Path: " << vfs.pwd() << std::endl;
    std::cout << "Current User: " << currentUser->username << std::endl;

    while (true) {
        std::cout << vfs.pwd() << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        execute_command(command);
    }
}

void VFSApp::execute_command(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> parts;
    std::string word;
    while (iss >> word) {
        parts.push_back(word);
    }

    if (parts.empty()) {
        return;
    }

    if (parts[0] == "sudo" && parts.size() > 1) {
        if (currentUser->isAdmin) {
            parts.erase(parts.begin());
            execute_command_without_sudo(parts);
        } 
        else {
            std::cout << "Error: You do not have sudo privileges." << std::endl;
        }
    } 
    else {
        execute_command_without_sudo(parts);
    }
}

void VFSApp::execute_command_without_sudo(const std::vector<std::string>& parts) {
    std::string cmd = parts[0];
    if (cmd == "pwd") {
        std::cout << vfs.pwd() << std::endl;
    } 
    else if (cmd == "touch" && parts.size() == 2) {
        std::cout << vfs.touch(parts[1]) << std::endl;
    } 
    else if (cmd == "mkdir" && parts.size() == 2) {
        std::cout << vfs.mkdir(parts[1]) << std::endl;
    } 
    else if (cmd == "cd" && parts.size() == 2) {
        std::cout << vfs.cd(parts[1]) << std::endl;
    } 
    else if (cmd == "rm" && parts.size() == 2) {
        std::cout << vfs.rm(parts[1]) << std::endl;
    } 
    else if (cmd == "ls") {
        bool showAll = (std::find(parts.begin(), parts.end(), "-a") != parts.end());
        std::cout << vfs.ls(showAll) << std::endl;
    } 
    else if (cmd == "ll") {
        std::cout << vfs.ll() << std::endl;
    } 
    else if (cmd == "cp" && parts.size() == 3) {
        std::cout << vfs.cp(parts[1], parts[2]) << std::endl;
    } 
    else if (cmd == "mv" && parts.size() == 3) {
        std::cout << vfs.mv(parts[1], parts[2]) << std::endl;
    } 
    else if (cmd == "tree") {
        std::cout << vfs.show_tree() << std::endl;
    } 
    else if (cmd == "help") {
        if (parts.size() == 2) {
            show_help(parts[1]);
        } 
        else {
            show_help();
        }
    } 
    else if (cmd == "about") {
        show_about();
    } 
    else if (cmd == "find" && parts.size() == 2) {
        std::cout << vfs.find(parts[1]) << std::endl;
    } 
    else {
        std::cout << "Error: Unknown command or incorrect syntax." << std::endl;
    }
}

void VFSApp::show_help(const std::string& cmd) {
    if (cmd.empty()) {
        std::cout << "Help Menu: \n";
        std::cout << "pwd: Show current directory\n";
        std::cout << "touch <filename>: Create a new file\n";
        std::cout << "mkdir <dirname>: Create a new directory\n";
        std::cout << "cd <path>: Change directory\n";
        std::cout << "rm <filename/dirname>: Remove a file or directory\n";
        std::cout << "ls: List files in current directory\n";
        std::cout << "ll: List files with detailed info\n";
        std::cout << "cp <source> <destination>: Copy a file or directory\n";
        std::cout << "mv <source> <destination>: Move a file or directory\n";
        std::cout << "tree: Show directory tree\n";
        std::cout << "help <command>: Show help for a specific command\n";
        std::cout << "about: Show information about this application\n";
    } 
    else {
        if (cmd == "pwd") {
            std::cout << "pwd: Prints the current working directory.\n";
        } 
        else if (cmd == "touch") {
            std::cout << "touch <filename>: Creates a new file with the specified name.\n";
        } 
        else if (cmd == "mkdir") {
            std::cout << "mkdir <dirname>: Creates a new directory with the specified name.\n";
        } 
        else if (cmd == "cd") {
            std::cout << "cd <path>: Changes the current directory to the specified path.\n";
        } 
        else if (cmd == "rm") {
            std::cout << "rm <filename/dirname>: Removes a file or directory.\n";
        } 
        else if (cmd == "ls") {
            std::cout << "ls: Lists the files in the current directory.\n";
        } 
        else if (cmd == "ll") {
            std::cout << "ll: Lists the files with detailed information (like [DIR] or [FILE]).\n";
        } 
        else if (cmd == "cp") {
            std::cout << "cp <source> <destination>: Copies a file or directory from source to destination.\n";
        } 
        else if (cmd == "mv") {
            std::cout << "mv <source> <destination>: Moves a file or directory from source to destination.\n";
        } 
        else if (cmd == "tree") {
            std::cout << "tree: Displays the directory structure of the current directory.\n";
        } 
        else {
            std::cout << "Error: Unknown command.\n";
        }
    }
}

void VFSApp::show_about() {
    std::cout << "Virtual File System: A simulated file system for learning and experimentation.\n";
    std::cout << "This app allows you to create, remove, list, move, and copy files and directories.\n";
    std::cout << "It also supports a simple directory structure with commands similar to Unix/Linux.\n";
}
