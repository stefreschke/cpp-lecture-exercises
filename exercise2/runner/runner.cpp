
#include <string>
#include <iostream>
#include <csignal>
#include "externallibrary.h"

// Expected calls:
// ./runner 1
// ./runner 1000000


void sighandler(int signum) {
    static int count{0};
    switch (signum) {
        case SIGSEGV:
            std::cout << "SIGSEGV found" << std::endl;
            // exit(1);
            break;
        case SIGFPE:
            std::cout << "SIGFPE found" << std::endl;
            break;
        case SIGTERM:
            std::cout << "SIGTERM found" << std::endl;
            break;
        case SIGILL:
            std::cout << "SIGILL found" << std::endl;
            break;
        case SIGABRT:
            std::cout << "SIGABRT found" << std::endl;
            break;
        case SIGINT:
            if (++count > 1) {
                exit(1);
            } else {
                std::cout << "SIGINT found" << std::endl;
                break;
            }
        case SIGKILL:
            exit(1);
        case SIGSTOP:
            exit(1);

    }

}


int main(int argc, char * argv[])
{
    signal(SIGSEGV, sighandler);
    signal(SIGFPE, sighandler);
    signal(SIGTERM, sighandler);
    signal(SIGINT, sighandler);
    signal(SIGILL, sighandler);
    signal(SIGABRT, sighandler);

    bool dryRun = atoi(argv[1]) < 1000000;
    initialize(dryRun);
    while (running())
    {
        try
        {
            processEvents();
        }
        catch (std::exception& e)
        {
            std::cerr << "No event processing : " << e.what() << std::endl;
        }
    }

    return 0;
}
