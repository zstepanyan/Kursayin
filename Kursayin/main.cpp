#include "FileSystem.h"
#include <iostream>



int main() {
    FileSystem fs;
    fs.mkdir("docs");
    fs.mkdir("images");
    fs.ls();  // Lists contents of the root directory

    return 0;
}