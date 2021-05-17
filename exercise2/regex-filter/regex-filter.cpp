
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std::string_literals;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "No regex passed" << std::endl;

        return -1;
    }

    // Input
    
    const auto filename = "emails.txt"s;
    std::ifstream file(filename, std::ios::in);

    if (!file.good())
    {
        std::cerr << "Unable to read file " << filename << std::endl;
        return -2;
    }

    file.seekg(0, std::ios::end);
    const auto contents_length = file.tellg();
    file.seekg(0, std::ios::beg);

    if (contents_length <= 0)
    {
        std::cerr << "No contents in " << filename << std::endl;
        return -3;
    }

    auto line = std::string("");
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        lines.push_back(std::move(line));
    }
    
    // Todo: filter
    
    // Todo: count
    
    // Todo: output

    for (const auto & line : lines) {
        std::cout << line << '\n';
    }

    std::cout.flush();
    
    return 0;
}
