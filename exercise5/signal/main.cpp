
#include <string>
#include <iostream>

#include "Signal.h"

class Emitter
{
public:
    Signal<> fire;
    Signal<int> update;
    Signal<int, const std::string &> errorHandler;

    void emit()
    {
        fire.emit();
        update.emit(42);
        errorHandler.emit(1, "Program termination imminent");
    }
};

class ErrorOutput
{
public:
    ErrorOutput() = default;

    void print(int errorCode, const std::string & errorMessage)
    {
        std::cout << "member function fired" << std::endl;
        std::cout << "Errorcode: " << errorCode << std::endl;
        std::cout << "Message: " << errorMessage << std::endl;
    }
};

void f()
{
    std::cout << "function fired" << std::endl;
}

int main(int argc, char * argv[])
{
    Emitter e;
    ErrorOutput output;

    e.fire.connect(f);
    e.update.connect([](int i) { std::cout << "lambda fired: " << i << std::endl; });

    const std::function<void(const ErrorOutput, int, const std::string &)> stuff = &ErrorOutput::print;
    e.errorHandler.connect(output, stuff);

    // directly connecting without cast won't compile,
    // I don't understand why, do you have an idea?

    // e.errorHandler.connect(output, &ErrorOutput::print);

    e.emit();
}
