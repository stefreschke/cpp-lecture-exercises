
#include <string>
#include <iostream>
#include <csignal>
#include <fstream>
#include <set>
#include "externallibrary.h"

// Expected calls:
// ./runner 1
// ./runner 1000000

std::set<std::string> signals;
std::set<std::string> exceptions;

void write_file() {
    std::ofstream myfile("errors.txt");
    myfile << "Exceptions:" << std::endl;
    for (auto ex : exceptions) {
        myfile << ex << std::endl;
    }
    myfile << std::endl << "Signals:" << std::endl;
    for (auto sig : signals) {
        myfile << sig << std::endl;
    }
    myfile.close();
}

void one_for_all_handler(int signum) {
    static int count{0};
    switch (signum) {
        case SIGSEGV:
            std::cout << "SIGSEGV found" << std::endl;
            signals.insert("SIGSEGV");
            break;
        case SIGFPE:
            std::cout << "SIGFPE found" << std::endl;
            signals.insert("SIGFPE");
            break;
        case SIGTERM:
            std::cout << "SIGTERM found" << std::endl;
            signals.insert("SIGTERM");
            break;
        case SIGILL:
            std::cout << "SIGILL found" << std::endl;
            signals.insert("SIGILL");
            break;
        case SIGABRT:
            std::cout << "SIGABRT found" << std::endl;
            signals.insert("SIGABRT");
            break;
        case SIGINT:
            signals.insert("SIGINT");
            if (++count > 1) {
                exit(1);
            } else {
                std::cout << "SIGINT found" << std::endl;
                write_file();
                break;
            }
        case SIGKILL:
            signals.insert("SIGKILL");
            exit(1);
        case SIGSTOP:
            signals.insert("SIGSTOP");
            exit(1);
    }

}


int main(int argc, char * argv[])
{
    signal(SIGSEGV, one_for_all_handler);
    signal(SIGFPE, one_for_all_handler);
    signal(SIGTERM, one_for_all_handler);
    signal(SIGINT, one_for_all_handler);
    signal(SIGILL, one_for_all_handler);
    signal(SIGABRT, one_for_all_handler);

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
            std::string stuff(e.what());
            exceptions.insert(stuff);
        }
    }
    write_file();

    return 0;
}
