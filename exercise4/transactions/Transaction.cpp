
#include "Transaction.h"

#include <iostream>


Transaction::Transaction(const std::string & name)
: m_name{ name }
{
}


const std::string & Transaction::name() const
{
    return m_name;
}


void Transaction::process(const std::string & operation)
{
    onBeforeProcess(operation);

    std::cout << "TA '" << m_name << "': " << operation << std::endl;

    onAfterProcess(operation);
}


void Transaction::onBeforeProcess(const std::string & operation)
{
}


void Transaction::onAfterProcess(const std::string & operation)
{
}

/**
 * a.)
 */
SecuredTransaction::SecuredTransaction(const std::string & name) : Transaction(name) {
    // nothing else to do
}

void SecuredTransaction::onBeforeProcess(const std::string &operation)
{
    std::cout << "Set up security" << std::endl;
}


void SecuredTransaction::onAfterProcess(const std::string & operation)
{
    std::cout << "Tear down security" << std::endl;
}

LoggedTransaction::LoggedTransaction(const std::string & name) : Transaction(name) {
    // nothing else to do
}

void LoggedTransaction::onBeforeProcess(const std::string & operation)
{
    std::cout << "Set up Logging" << std::endl;
}


void LoggedTransaction::onAfterProcess(const std::string & operation)
{
    std::cout << "Tear down Logging" << std::endl;
}

LoggedSecureTransaction::LoggedSecureTransaction(const std::string & name) : LoggedTransaction(name),
                                                                             SecuredTransaction(name) {
    // nothing else to do
}

void LoggedSecureTransaction::process(const std::string &operation) {
    SecuredTransaction::onBeforeProcess(operation);
    LoggedTransaction::onBeforeProcess(operation);

    std::cout << "TA '" << this->LoggedTransaction::name() << "': " << operation << std::endl;

    LoggedTransaction::onAfterProcess(operation);
    SecuredTransaction::onAfterProcess(operation);
}

/**
 * b.) done in header only
 */


