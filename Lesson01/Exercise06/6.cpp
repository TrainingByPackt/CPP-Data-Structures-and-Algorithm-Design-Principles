#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }

    // vector has now 10 elements {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    std::cout << "Vector after inserting elements : ";
    for (auto i : vec)
        std::cout << i << " ";
    std::cout << std::endl;

    vec.pop_back();         // vector has now 10 elements {0, 1, 2, 3, 4, 5, 6, 7, 8}
    vec.pop_back();         // vector has now 8 elements {0, 1, 2, 3, 4, 5, 6, 7}
    vec.erase(vec.begin()); // vector has now 7 elements {1, 2, 3, 4, 5, 6, 7}

    vec.erase(vec.begin() + 1, vec.begin() + 4);
    // Now, vector has 4 elements {1, 5, 6, 7}
    std::cout << "Vector after removing elements : ";
    for (auto i : vec)
        std::cout << i << " ";
}
