
#include <array>
#include <initializer_list>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "collect.h"


int main(int argc, char * argv[])
{
    const auto intVector   = std::vector<int>{0, 1, 2, 3, 4};
    const auto intInitList = {0, 1, 2, 3, 4};
    const auto intBoolMap  = std::map<int, bool>{{1, false}, {4, true}, {2, true}, {3, false}, {5, false}};
    const auto doubleSet   = std::set<double>{0.0, 3.2, 4.1, 5.7, 8.9};

    // Fully specified result type
    {
        std::vector<float> vfc = collect<std::vector<float>>(intInitList, [](int v) { return static_cast<float>(v); });
        std::list<float>   lfc = collect<std::list<float>>(intVector, [](int v) { return static_cast<float>(v); });
        std::set<int>      sic = collect<std::set<int>>(doubleSet, [](double v) { return static_cast<int>(v); });
        std::unordered_set<int> usic
            = collect<std::unordered_set<int>>(doubleSet, [](double v) { return static_cast<int>(v); });
        std::vector<int>     vic = collect<std::vector<int>>(doubleSet, [](double v) { return static_cast<int>(v); });
        std::vector<bool>    vbc = collect<std::vector<bool>>(intBoolMap, [](const auto & p) { return p.second; });
        std::map<int, float> mif
            = collect<std::map<int, float>>(intVector, [](int i) { return std::make_pair(i, static_cast<float>(i)); });
        std::unordered_map<int, float> umif = collect<std::unordered_map<int, float>>(
            intVector, [](int i) { return std::make_pair(i, static_cast<float>(i)); });
    }


    // Challenge: deduce result value type
    // comment in all lines your solution can handle
    {
        // std::vector<float>      vfc = collect<std::vector>(intInitList, [](int v) { return static_cast<float>(v); });
        // std::list<float>        lfc = collect<std::list>(intVector, [](int v) { return static_cast<float>(v); });
        // std::set<int>           sic = collect<std::set>(doubleSet, [](double v) { return static_cast<int>(v); });
        // std::unordered_set<int> usic
        //    = collect<std::unordered_set>(doubleSet, [](double v) { return static_cast<int>(v); });
        // std::vector<int>     vic = collect<std::vector>(doubleSet, [](double v) { return static_cast<int>(v); });
        // std::vector<bool>    vbc = collect<std::vector>(intBoolMap, [](const auto & p) { return p.second; });
        // std::map<int, float> mif
        //    = collect<std::map>(intVector, [](int i) { return std::make_pair(i, static_cast<float>(i)); });
        // std::unordered_map<int, float> umif
        //    = collect<std::unordered_map>(intVector, [](int i) { return std::make_pair(i, static_cast<float>(i)); });
    }

    // Challenge: deduce result value and container type
    // comment in all lines your solution can handle
    {
        // std::vector<float>   vfc = collect(intVector, [](int v) { return static_cast<float>(v); });
        // std::set<int>        sic = collect(doubleSet, [](double v) { return static_cast<int>(v); });
        // std::map<int, float> mif
        //    = collect(intBoolMap, [](const auto & p) { return std::make_pair(p.first, static_cast<float>(p.second));
        //    });
    }
}
