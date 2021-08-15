
#include <iostream>
#include <memory>

#include "Graph.h"

/** generated graph
* 0
*  1
*   6
*     15 : 3
*     16 : 2
*   7
*     17 : 5
*     18 : 1
*   8 : 6
*  2
*   9  : 3
*   10 : 2
*   11 : 4
*  3
*   12 : 9
*  4
*   13 : 1
*  5
*   14 -> 2
*/
std::unique_ptr<Node> generateGraph()
{
    auto n0  = std::make_unique<Group>(0);
    auto n1  = std::make_unique<Group>(1);
    auto n2  = std::make_unique<Group>(2);
    auto n3  = std::make_unique<Group>(3);
    auto n4  = std::make_unique<Group>(4);
    auto n5  = std::make_unique<Group>(5);
    auto n6  = std::make_unique<Group>(6);
    auto n7  = std::make_unique<Group>(7);
    auto n8  = std::make_unique<Leaf >(8 , 6);
    auto n9  = std::make_unique<Leaf >(9 , 3);
    auto n10 = std::make_unique<Leaf >(10, 2);
    auto n11 = std::make_unique<Leaf >(11, 4);
    auto n12 = std::make_unique<Leaf >(12, 9);
    auto n13 = std::make_unique<Leaf >(13, 1);
    auto n14 = std::make_unique<Proxy>(14, n2.get());
    auto n15 = std::make_unique<Leaf >(15, 3);
    auto n16 = std::make_unique<Leaf >(16, 2);
    auto n17 = std::make_unique<Leaf >(17, 5);
    auto n18 = std::make_unique<Leaf >(18, 1);
    
    n7->appendNode(std::move(n17));
    n7->appendNode(std::move(n18));
    
    n6->appendNode(std::move(n15));
    n6->appendNode(std::move(n16));
    
    n5->appendNode(std::move(n14));
    
    n4->appendNode(std::move(n13));
    
    n3->appendNode(std::move(n12));
    
    n2->appendNode(std::move(n9));
    n2->appendNode(std::move(n10));
    n2->appendNode(std::move(n11));
    
    n1->appendNode(std::move(n6));
    n1->appendNode(std::move(n7));
    n1->appendNode(std::move(n8));

    n0->appendNode(std::move(n1));
    n0->appendNode(std::move(n2));
    n0->appendNode(std::move(n3));
    n0->appendNode(std::move(n4));
    n0->appendNode(std::move(n5));
    return std::move(n0);
}

int main(int argc, char * argv[])
{
    auto graph = generateGraph();
    graph->print(std::cout);
    std::cout << "Total weight: " << graph->weight() << std::endl;
}
