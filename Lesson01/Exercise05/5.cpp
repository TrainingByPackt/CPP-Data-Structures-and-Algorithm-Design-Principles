#include <algorithm>
#include <iostream>
#include <vector>

struct student
{
    std::string name;
    int standard;
};

std::ostream &operator<<(std::ostream &os, const student &s)
{
    return (os << "[Name: " << s.name << ", Standard: " << s.standard << "]");
}

int main()
{
    std::vector<student> students; // Empty vector {}
    students.push_back(student{"Rahul", 10});
    students.push_back(student{"Viraj", 12});

    students.insert(students.begin(), student{"Raj", 6});
    students.insert(std::find_if(students.begin(), students.end(),
                                 [](const student &s) {
                                     return s.name == "Viraj";
                                 }),
                    student{"Sachin", 14});
    // Vector has 45 elements {-1, 0, 4, 1, 2}

    std::cout << "Vector after inserting elements: ";
    for (auto i : students)
        std::cout << i << ", "; // Prints -1 0 4 1 2
}
