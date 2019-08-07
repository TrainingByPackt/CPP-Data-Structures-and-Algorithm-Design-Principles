#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;
class hash_map
{
    std::vector<std::list<int>> data;

public:
    hash_map(size_t n)
    {
        data.resize(n);
    }

    void insert(uint value)
    {
        int n = data.size();
        data[value % n].push_back(value);
        std::cout << "Inserted " << value << std::endl;
    }

    bool find(uint value)
    {
        int n = data.size();
        auto &entries = data[value % n];
        return std::find(entries.begin(), entries.end(), value) != entries.end();
    }

    void erase(uint value)
    {
        int n = data.size();
        auto &entries = data[value % n];
        auto iter = std::find(entries.begin(), entries.end(), value);

        if (iter != entries.end())
        {
            entries.erase(iter);
            std::cout << "Removed " << value << std::endl;
        }
    }
};

int main()
{
    hash_map map(100); // Let’s go with 100 as its easier for calculation.

    auto print = [&](int value) {
        if (map.find(value))
            std::cout << value << " found in the hash map";
        else
            std::cout << value << " NOT found in the hash map";
        std::cout << std::endl;
    };

    map.insert(3135); // Inserts at position 35
    map.insert(3);    // Inserts at position 3
    map.insert(34);   // Inserts at position 34

    print(35);
    print(34);
    print(10);

    map.insert(55);
    map.erase(155);
    print(55);
    map.erase(55);
    print(55);

    map.insert(100);
    map.insert(0);
    print(0);
    print(100);
}
