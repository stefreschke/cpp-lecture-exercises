
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std::string_literals;

int main(int argc, char** argv)
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

    std::string str(argv[1]);
    bool case_sensitive = true;
    if (argc > 2) {
        std::string sensitivity_arg(argv[2]);
        if (sensitivity_arg == "icase") {
            case_sensitive = false;
        }
    }
    std::regex re;
    if (case_sensitive) {
        re = std::regex(str);
    } else {
        re = std::regex(str, std::regex_constants::icase);
    }
    std::map<std::string, int> map{};
    for (const auto & l : lines) {
        std::smatch base_match;
        if (std::regex_match(l, base_match, re)) {
            if (base_match.size() >= 2) {
                auto sub_match_str = base_match[1].str();
                if (!case_sensitive) {
                    std::transform(sub_match_str.begin(), sub_match_str.end(), sub_match_str.begin(),
                                    [](unsigned char c){ return std::tolower(c); });
                }
                if (map.contains(sub_match_str)) {
                    auto stuff = map[sub_match_str];
                    map[sub_match_str] = stuff + 1;
                } else {
                    map[sub_match_str] = 1;
                }
            }
        }
    }
    for (const auto& entry : map) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    std::cout.flush();
    
    return 0;
}
