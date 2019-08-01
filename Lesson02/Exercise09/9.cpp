#include <iostream>
#include <vector>
#include <queue>

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
    std::vector<std::vector<std::pair<int, int>>> data;

    graph(int n)
    {
        data = std::vector(n, std::vector<std::pair<int, int>>());
    }

    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "ADD: " << c1 << "-" << c2 << "=" << dis << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1].push_back({n2, dis});
        data[n2].push_back({n1, dis});
    }

    void bfs(int start = 0)
    {
        std::vector<bool> visited(data.size(), false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        while (not q.empty())
        {
            auto cur = q.front();
            std::cout << static_cast<city>(cur) << " ";
            q.pop();
            for (auto child : data[cur])
            {
                if (not visited[child.first])
                {
                    visited[child.first] = true;
                    q.push(child.first);
                }
            }
        }
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

    std::cout << "BFS: ";
    g.bfs();

    return 0;
}
