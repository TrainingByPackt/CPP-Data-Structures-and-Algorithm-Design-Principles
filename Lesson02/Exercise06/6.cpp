#include <iostream>
#include <vector>

enum class city : int
{
    DELHI,
    AHMEDABAD,
    MUMBAI,
    KOLKATA,
    GOA,
    BENGALURU,
    CHENNAI
};

std::ostream &operator<<(std::ostream &os, const city c)
{
    switch (c)
    {
    case city::DELHI:
        os << "DELHI";
        return os;
    case city::AHMEDABAD:
        os << "AHMEDABAD";
        return os;
    case city::MUMBAI:
        os << "MUMBAI";
        return os;
    case city::KOLKATA:
        os << "KOLKATA";
        return os;
    case city::GOA:
        os << "GOA";
        return os;
    case city::BENGALURU:
        os << "BENGALURU";
        return os;
    case city::CHENNAI:
        os << "CHENNAI";
        return os;
    default:
        return os;
    }
}

struct graph
{
    std::vector<std::vector<int>> data;

    graph(int n)
    {
        data.reserve(n);
        std::vector<int> row(n);
        std::fill(row.begin(), row.end(), -1);
        for (int i = 0; i < n; i++)
        {
            data.push_back(row);
        }
    }

    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "ADD: " << c1 << "-" << c2 << "=" << dis << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = dis;
        data[n2][n1] = dis;
    }

    void removeEdge(const city c1, const city c2)
    {
        std::cout << "REMOVE: " << c1 << "-" << c2 << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = -1;
        data[n2][n1] = -1;
    }
};

int main()
{
    graph g(7);
    g.addEdge(city::AHMEDABAD, city::DELHI, 900);
    g.addEdge(city::AHMEDABAD, city::MUMBAI, 500);
    g.addEdge(city::AHMEDABAD, city::GOA, 1000);
    g.addEdge(city::MUMBAI, city::DELHI, 1000);
    g.addEdge(city::MUMBAI, city::GOA, 500);
    g.addEdge(city::GOA, city::BENGALURU, 200);
    g.addEdge(city::MUMBAI, city::KOLKATA, 1500);
    g.addEdge(city::GOA, city::CHENNAI, 500);
    g.addEdge(city::DELHI, city::KOLKATA, 1000);
    g.addEdge(city::BENGALURU, city::CHENNAI, 300);
    g.addEdge(city::KOLKATA, city::CHENNAI, 700);

    g.addEdge(city::KOLKATA, city::AHMEDABAD, 1800);
    g.removeEdge(city::KOLKATA, city::AHMEDABAD);

    return 0;
}