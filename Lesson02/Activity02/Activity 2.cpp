#include <iostream>
#include <vector>
#include <limits>
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

    std::vector<int> dijkstra(const city source)
    {
        using heap_node = std::pair<int, int>;
        std::priority_queue<heap_node, std::vector<heap_node>, std::greater<heap_node>> pq;

        std::vector<int> distances(data.size(), std::numeric_limits<int>::max());
        int source_id = static_cast<int>(source);
        pq.push({0, source_id});
        distances[source_id] = 0;

        while (not pq.empty())
        {
            auto next_node = pq.top().second;
            pq.pop();

            for (auto child : data[next_node])
            {
                auto dis = child.first;
                auto vertex = child.second;
                if (distances[vertex] > distances[next_node] + dis)
                {
                    distances[vertex] = distances[next_node] + dis;
                    pq.push({distances[vertex], vertex});
                }
            }
        }

        return distances;
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

    auto abadDistances = g.dijkstra(city::AHMEDABAD);
    std::cout << "Distances from Ahmedabad to other cities:" << std::endl;
    for (int i = 0; i < abadDistances.size(); i++)
    {
        std::cout << static_cast<city>(i) << ": " << abadDistances[i] << std::endl;
    }

    auto kktDistances = g.dijkstra(city::KOLKATA);
    std::cout << "Distances from Kolkata to other cities:" << std::endl;
    for (int i = 0; i < kktDistances.size(); i++)
    {
        std::cout << static_cast<city>(i) << ": " << kktDistances[i] << std::endl;
    }

    return 0;
}
