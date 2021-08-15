
#pragma once


#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <memory>


/**
 * base code
 */

class Transaction {
public:
    explicit Transaction(const std::string &name);

    virtual ~Transaction() = default;

    const std::string &name() const;

    virtual void process(const std::string &operation);


protected:
    virtual void onBeforeProcess(const std::string &operation);

    virtual void onAfterProcess(const std::string &operation);


private:
    std::string m_name;
};

/**
 * a.)
 */

class SecuredTransaction : public Transaction {
public:
    explicit SecuredTransaction(const std::string &name);

    void onBeforeProcess(const std::string &operation) override;

    void onAfterProcess(const std::string &operation) override;
};

class LoggedTransaction : public Transaction {
public:
    explicit LoggedTransaction(const std::string &name);

    void onBeforeProcess(const std::string &operation) override;

    void onAfterProcess(const std::string &operation) override;
};

class LoggedSecureTransaction
        : public SecuredTransaction, public LoggedTransaction {
public:
    explicit LoggedSecureTransaction(const std::string &name);

    void process(const std::string &operation) override;
};

/**
 * b.)
 */
class SetUpsAndTearDowns {
public:
    virtual void onBeforeProcess(const std::string &operation) = 0;

    virtual void onAfterProcess(const std::string &operation) = 0;
};

class Logging : public SetUpsAndTearDowns {
public:
    void onBeforeProcess(const std::string &operation) override {
        std::cout << "Set up Logging" << std::endl;
    }

    void onAfterProcess(const std::string &operation) override {
        std::cout << "Tear Down Logging" << std::endl;
    }

};

class Security : public SetUpsAndTearDowns {
public:
    void onBeforeProcess(const std::string &operation) override {
        std::cout << "Set up Security" << std::endl;
    }

    void onAfterProcess(const std::string &operation) override {
        std::cout << "Tear down Security" << std::endl;
    }
};

class MultipleSetUpsAndTearDownsTransaction : Transaction {
public:
    static MultipleSetUpsAndTearDownsTransaction
    loggedAndSecuredTransaction(const std::string &name) {
        std::vector<std::unique_ptr<SetUpsAndTearDowns>> strats{};
        strats.emplace_back(std::make_unique<Logging>());
        strats.emplace_back(std::make_unique<Security>());
        return MultipleSetUpsAndTearDownsTransaction{
                std::move(strats), name};
    }

    static MultipleSetUpsAndTearDownsTransaction
    loggedTransaction(const std::string &name) {
        std::vector<std::unique_ptr<SetUpsAndTearDowns>> strats{};
        strats.emplace_back(std::make_unique<Logging>());
        return MultipleSetUpsAndTearDownsTransaction{
                std::move(strats), name};
    }

    static MultipleSetUpsAndTearDownsTransaction
    securedTransaction(const std::string &name) {
        std::vector<std::unique_ptr<SetUpsAndTearDowns>> strats{};
        strats.emplace_back(std::make_unique<Security>());
        return MultipleSetUpsAndTearDownsTransaction{
                std::move(strats), name};
    }

    void process(const std::string &operation) override {
        onBeforeProcess(operation);
        std::cout << "TA '" << Transaction::name() << "': " << operation
                  << std::endl;
        onAfterProcess(operation);
    }

protected:
    void onBeforeProcess(const std::string &operation) override {
        for (auto &setUp : setUpsAndTearDowns) {
            setUp->onBeforeProcess(operation);
            setUpsAndTearDownsStack.push(std::move(setUp));
        }
    }

    void onAfterProcess(const std::string &operation) override {
        while (!setUpsAndTearDownsStack.empty()) {
            auto &tearDown = setUpsAndTearDownsStack.top();
            tearDown->onAfterProcess(operation);
            setUpsAndTearDownsStack.pop();
            std::move(tearDown);
        }
    }

    MultipleSetUpsAndTearDownsTransaction(
            std::vector<std::unique_ptr<SetUpsAndTearDowns>> new_setup_teardowns,
            const std::string &name) : Transaction(name) {
        setUpsAndTearDowns = std::move(new_setup_teardowns);
        this->setUpsAndTearDownsStack = std::stack<std::unique_ptr<SetUpsAndTearDowns>>{};
    }


private:
    std::vector<std::unique_ptr<SetUpsAndTearDowns>> setUpsAndTearDowns;
    // I think this is okay, because Transactions will be single-threaded?
    std::stack<std::unique_ptr<SetUpsAndTearDowns>> setUpsAndTearDownsStack;
};
