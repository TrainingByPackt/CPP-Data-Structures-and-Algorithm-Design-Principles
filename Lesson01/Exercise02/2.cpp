#include <array>
#include <iostream>
int main()
{

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};

    std::cout << "Comparing two C-arrays for equality: " << (arr1 == arr2) << std::endl; // Compares addresses of arr1 and arr2
    std::cout << "Comparing two C-arrays for less than: " << (arr1 < arr2) << std::endl; // Compares address of arr1 and arr2
    auto arr3 = arr1;                                                                    // arr3 now points to arr1, without creating a new copy

    std::array<int, 5> sarr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> sarr2 = {1, 2, 3, 4, 5};
    std::array<int, 5> sarr3 = {1, 10, 3, 4, 5};
    std::cout << "Comparing two std-arrays for equality: " << (sarr1 == sarr2) << std::endl; // Prints 1
    std::cout << "Comparing two std-arrays for less than: " << (sarr1 < sarr3);              // Prints 1
    auto sarr4 = sarr1;

    return 0;
}
