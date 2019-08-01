#include <iostream>
#include <forward_list>

int main()
{

    std::forward_list<int> fwd_list = {1, 2, 3};
    std::cout << "Forward list after init : ";
    for (auto i : fwd_list)
        std::cout << i << " "; // Prints 1 2 3
    std::cout << std::endl;

    fwd_list.push_front(0); // list becomes {0, 1, 2, 3}
    auto it = fwd_list.begin();
    fwd_list.insert_after(it, 5); // list becomes {0, 5, 1, 2, 3}
    fwd_list.insert_after(it, 6); // list becomes {0, 6, 5, 1, 2, 3}
    std::cout << "Forward list after insertions : ";
    for (auto i : fwd_list)
        std::cout << i << " ";
}
