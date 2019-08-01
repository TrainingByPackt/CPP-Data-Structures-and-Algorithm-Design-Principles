#include <iostream>
#include <forward_list>

int main()
{
    std::forward_list<int> fwd_list = {1, 2, 3, 4, 5};

    fwd_list.pop_front(); // list becomes {2, 3, 4, 5}
    auto it = fwd_list.begin();
    fwd_list.erase_after(it); // list becomes {2, 4, 5}

    fwd_list.erase_after(it, fwd_list.end()); // list becomes {2}
    std::cout << "Forward list after deletions : ";
    for (auto i : fwd_list)
        std::cout << i << " ";
}
