
#ifndef EXERCISE4_GRAPH_H
#define EXERCISE4_GRAPH_H

#include <utility>
#include <vector>
#include <memory>

class Node {
public:
    virtual void print(std::ostream & maybeCOut) {
        writeDepthBlanks(maybeCOut);
        maybeCOut << id << std::endl;
    }

    virtual size_t weight() = 0;

    virtual void appendNode(std::unique_ptr<Node> node) = 0;

    [[nodiscard]] size_t getId() const {
        return id;
    }

    void setDepthTo(size_t target) {
        this->depth = target + 1;
    }

protected:
    size_t id;
    size_t depth;

    explicit Node(size_t id) {
        this->id = id;
        this->depth = 0;
    }

    /**
     * Handle indenting for the expected output.
     * @param maybeCOut
     */
    void writeDepthBlanks(std::ostream & maybeCOut) const {
        for (int i = 1; i <= depth; i++) {
            maybeCOut << " ";
        }
    }
};

class Group : public Node {
public:

    void print(std::ostream & maybeCOut) override {
        writeDepthBlanks(maybeCOut);
        maybeCOut << id << std::endl;
        for (auto & next_one : next_ones) {
            next_one->setDepthTo(this->depth);
            next_one->print(maybeCOut);
        }
    }

    size_t weight() override {
        size_t sum = 0;
        for (auto & next_one : next_ones) {
            sum += next_one->weight();
        }
        return sum;
    }

    void appendNode(std::unique_ptr<Node> node) override {
        next_ones.push_back(std::move(node));
    }

    explicit Group(size_t id) : Node(id) {
        // nothing else to do
    }

private:
    std::vector<std::unique_ptr<Node>> next_ones;
};

class Leaf : public Node {
public:
    void print(std::ostream & maybeCOut) override {
        writeDepthBlanks(maybeCOut);
        maybeCOut << id << " : " << weightMember << std::endl;
    }

    size_t weight() override {
        return weightMember;
    }

    void appendNode(std::unique_ptr<Node> node) override {
        // not yet required by test case
        throw "not implemented";
    }

    Leaf(size_t id, size_t weight) : Node(id) {
        weightMember = weight;
    }
private:
    size_t weightMember;
};


class Proxy : public Node {
public:
    void print(std::ostream & maybeCOut) override {
        writeDepthBlanks(maybeCOut);
        maybeCOut << id << " -> " << subgraph->getId() << std::endl;
    }
    void appendNode(std::unique_ptr<Node> node) override {
        // not yet required by test case
        throw "not implemented";
    }

    Proxy(size_t id, Node* subgraph) : Node(id) {
        // ugly use of pointer, can't get my head around
        // how to do it with a smart pointer though
        this->subgraph = subgraph;
    }

    size_t weight() override {
        return subgraph->weight();
    }
private:
    Node* subgraph = nullptr;
};


#endif //EXERCISE4_GRAPH_H
