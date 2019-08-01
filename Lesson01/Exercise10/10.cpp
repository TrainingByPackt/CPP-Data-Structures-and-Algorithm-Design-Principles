#include <iostream>
#include <forward_list>

int main()
{
    using Point = std::pair<double, double>;
    std::forward_list<Point> points = {{1, 2}, {0, 4}, {4, 2}, {3, 10}, {9, 5}, {7, 8}, {8, 9}, {1, 2}, {4, 2}, {4, 3}};

    std::cout << "Initial list of points : ";
    for (auto point : points)
        std::cout << "(" << point.first << " " << point.second << "), ";
    std::cout << std::endl;

    points.sort(); // Pair by default sorts by first element, and if that is equal, it considers second element
    std::cout << "Sorted list of points: ";
    for (auto point : points)
        std::cout
            << "(" << point.first << " " << point.second << "), ";
    std::cout << std::endl;

    std::cout << "Reversed list of points: ";
    for (auto point : points)
        std::cout
            << "(" << point.first << " " << point.second << "), ";
    std::cout << std::endl;

    // Let’s remove duplicated entries in the list first:
    points.sort();
    points.unique();
    std::cout << "List of points after removing duplicate entries: ";
    for (auto point : points)
        std::cout
            << "(" << point.first << " " << point.second << "), ";
    std::cout << std::endl;

    // Now, let’s remove points which are nearby
    points.unique(
        [](const Point &p1, const Point &p2) {
            double distance = (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
            return distance < 1.5;
        });
    std::cout << "List of points after removing nearby entries: ";
    for (auto point : points)
        std::cout
            << "(" << point.first << " " << point.second << "), ";
    std::cout << std::endl;
}