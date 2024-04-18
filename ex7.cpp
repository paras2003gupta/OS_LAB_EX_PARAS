#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        cerr << "Fork failed." << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "This is the child process. PID: " << getpid() << endl;
    } else {
        // Parent process
        cout << "This is the parent process. Child PID: " << pid << ", Parent PID: " << getpid() << endl;
    }

    return 0;
}
