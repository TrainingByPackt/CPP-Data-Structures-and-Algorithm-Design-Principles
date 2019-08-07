#include <iostream>
#include <vector>

using uint = unsigned int;
class hash_map
{
    std::vector<int> data;

public:
    hash_map(size_t n)
    {
        data = std::vector(n, -1);
    }

    void insert(uint value)
    {
        int n = data.size();
        data[value % n] = value;
        std::cout << "Inserted " << value << std::endl;
    }

    bool find(uint value)
    {
        int n = data.size();
        return (data[value % n] == value);
    }

    void erase(uint value)
    {
        int n = data.size();
        if (data[value % n] == value)
        {
            data[value % n] = -1;
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
