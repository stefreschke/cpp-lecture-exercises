
#include <cassert>

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <chrono>

bool isPalindrome(std::string line) {
    return equal(line.begin(), line.begin() + line.size()/2, line.rbegin());
}


int main(int argc, char* argv[])
{
    // Input
    auto line = std::string("");
    std::vector<std::string> lines;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            continue;
        }

        const auto size = line.size();
        lines.push_back(std::move(line));
        line.reserve(size);
    }
    
    // const auto start = std::chrono::high_resolution_clock::now();
    
    // Todo: Implement algorithm to sort palindromes to the front of the list
    std::vector<int> palindromes;
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        std::string currentLine = *it;
        int index = std::distance(lines.begin(), it);
        if (isPalindrome(currentLine)) {
            palindromes.push_back(index);
        }
    }
    for (std::vector<int>::reverse_iterator it = palindromes.rbegin(); it != palindromes.rend(); ++it) {
        int id = *it;
        std::string value = lines[id];
        lines.push_back(std::move(value));
        lines.erase(lines.begin() + id);
    }
    std::rotate(lines.rbegin(), lines.rbegin() + palindromes.size(), lines.rend());


    // const auto end = std::chrono::high_resolution_clock::now();
    // const auto duration = end - start;
    // std::cout << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
    
    std::cout << "Sorted by palindromity" << std::endl << std::endl;
    for (const auto & s : lines)
    {
        std::cout << s << std::endl;
    }
    
    return 0;
}
