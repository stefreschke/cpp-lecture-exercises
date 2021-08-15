
#include <iostream>

#include "Transaction.h"


void testMI()
{
    // Basic transaction
    Transaction t1{ "t1" };
    t1.process("do something");
    std::cout << std::endl;

    // Transaction with logging
    LoggedTransaction t2{ "t2" };
    t2.process("do something with logging");
    std::cout << std::endl;

    // Secured transaction
    SecuredTransaction t3{ "t3" };
    t3.process("do something secured");
    std::cout << std::endl;

    // Secured transaction with logging
    LoggedSecureTransaction t4{ "t4" };
    t4.process("do something secured with logging");
    std::cout << std::endl;
}


void testNonMI()
{
    // Basic transaction
    Transaction t1{ "t1" };
    t1.process("do something");
    std::cout << std::endl;

    // Transaction with logging
    auto t2 = MultipleSetUpsAndTearDownsTransaction::loggedTransaction("t2");
    t2.process("do something with logging");
    std::cout << std::endl;

    // Secured transaction
    auto t3 = MultipleSetUpsAndTearDownsTransaction::securedTransaction("t3");
    t3.process("do something secured");
    std::cout << std::endl;

    // Secured transaction with logging
    auto t4 = MultipleSetUpsAndTearDownsTransaction::loggedAndSecuredTransaction("t4");
    t4.process("do something secured with logging");
    std::cout << std::endl;
}


int main(int argc, char * argv[])
{
    std::cout << "Testing MI implementation..." << std::endl;
    testMI();
    std::cout << std::endl;

    std::cout << "Testing non-MI implementation..." << std::endl;
    testNonMI();
    std::cout << std::endl;
}
