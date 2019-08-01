#include <array>
#include <iostream>

int main()
{
	std::array<int, 4> arr = {1, 2, 3, 4};
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << " "; // Prints 1 2 3 4
	}
}
