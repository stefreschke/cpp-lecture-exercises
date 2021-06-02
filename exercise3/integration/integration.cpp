#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <new>
#include <cassert>


//
// Note: the memory measurement is preliminary, we may use a different approach depending on the creativity of the implementations
//
auto memory = std::size_t{ 0 };

[[nodiscard]] void* operator new(std::size_t size)
{
    const auto ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc{};
    }
    memory += size;
    return ptr;
}

void operator delete(void* ptr, std::size_t size)
{
    std::free(ptr);
    memory -= size;
}


// Add any required definitions and implementations for Address
class Address
{
public:
    Address() {
        true_number = 1;
        true_postalcode = 13337;
        true_street = "swag";
        true_town = "land";
    }
    Address(std::string streetValue, int numberValue, int postalCodeValue, std::string townValue) {
        true_street = streetValue;
        true_town = townValue;
        true_number = numberValue;
        true_postalcode = postalCodeValue;
    }
    [[nodiscard]] std::string street() const {
        return true_street;
    }
    [[nodiscard]] std::string town() const {
        return true_town;
    }
    [[nodiscard]] int number() const {
        return true_number;
    }
    [[nodiscard]] int postalCode() const {
        return true_postalcode;
    }
    operator int() const { return true_number; }

    bool operator<(Address lhs) const {
        if (lhs.number() != number()) {
            return lhs.number() < number();
        } else if (lhs.street() != street()) {
            return lhs.street() < street();
        } else if (lhs.town() != town()) {
            return lhs.town() < town();
        } else {
            return lhs.postalCode() < postalCode();
        }
    }


    bool operator==(Address &lhs) const {
        return lhs.street() == street() && lhs.town() == town()
            && lhs.postalCode() == postalCode() && lhs.number() == number();
    }

    std::string true_street;
    std::string true_town;
    int true_number;
    int true_postalcode;
};

std::stringstream& operator>>(std::stringstream& lhs, Address& rhs) {
    while (!lhs.eof()) {
        std::string s;
        lhs >> s;
        std::cout << s;
    }
    std::cout << std::endl;
    return lhs;
}

namespace std
{
    template<> struct hash<Address>
    {
        std::size_t operator()(Address const& s) const noexcept
        {
            return ((hash<string>()(s.street()) ^ (hash<string>()(s.town()) << 1)) >> 1)
                   ^ (hash<int>()(s.postalCode()) << 1) ^ (hash<int>()(s.number()) << 1);
        }
    };
}


//
// Do not change the code below
//


int main(int argc, char* argv[])
{
    {
        auto vec = std::vector<std::pair<std::string, Address>>{};

        auto file = std::ifstream{ "addresses.txt" };
        if (!file) {
            std::cerr << "Failed to open file addresses.txt" << std::endl;
            return EXIT_FAILURE;
        }
        while (file) {
            std::string firstName, lastName;
            auto fields = std::tuple<std::string, int, int, std::string>{};
            if (file >> firstName >> lastName >> std::get<0>(fields) >> std::get<1>(fields) >> std::get<2>(fields) >> std::get<3>(fields)) {
                const auto address = std::make_from_tuple<Address>(fields);
                assert(address.street() != "" && address.number() > 0 && address.postalCode() > 0 && address.town() != "");
                vec.emplace_back(firstName + " " + lastName, address);
            }
        }

        std::cout << "Memory: " << memory << std::endl;

        std::map<Address, std::vector<std::string>> treemap;
        for (const auto& item : vec) {
            if (item.second) {
                treemap[item.second].push_back(item.first);
            }
        }

        std::unordered_map<Address, std::size_t> hashmap;
        for (const auto& item : treemap) {
            // serialize it
            std::stringstream data;
            data << item.first;
            // deserialize it
            Address address;
            data >> address;
            hashmap[address] = size(item.second);
        }

        for (const auto& item : hashmap) {
            // Extra challenge (for fun): make the line below work instead
            // const auto& [street, number, postalCode, town] = static_cast<std::tuple<std::string, int, int, std::string>>(item.first);
            const auto& [street, number, postalCode, town] = item.first;
            std::cout << item.first << ": " << street << " " << number << ", " << postalCode << " " << town << std::endl;
        }
    }

    std::cout << "Memory: " << memory << std::endl;
}
