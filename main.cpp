#include <iostream>
#include "VFSApp.h"

int main() {
    VFSApp app;
    app.setUser("admin", true);  // Example of setting an admin user
    app.run();

    return 0;
}