#include <iostream>
#include <deque>

void enterQueue(std::deque<std::string> &boardingQueue, const std::string &name, const std::string &ticket = "Economy")
{
    if (ticket == "Economy")
        boardingQueue.push_back(name);
    else if (ticket == "Business")
        boardingQueue.push_front(name);
}

void boardFlight(std::deque<std::string> &boardingQueue)
{
    std::cout << boardingQueue.front() << " boarded the flight" << std::endl;
    boardingQueue.pop_front();
}

void remove(std::deque<std::string> &boardingQueue, const std::string &name)
{
    auto it = std::find(boardingQueue.begin(), boardingQueue.end(), name);
    if (it != boardingQueue.end())
    {
        boardingQueue.erase(it);
        std::cout << name << " removed from the queue." << std::endl;
    }
    else
        std::cout << name << " is not present in the queue." << std::endl;
}

void print(const std::deque<std::string> &boardingQueue)
{
    for (const auto &person : boardingQueue)
    {
        std::cout << person << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::deque<std::string> flight1;
    enterQueue(flight1, "Raj");
    enterQueue(flight1, "Sachin");
    enterQueue(flight1, "Viraj");

    std::cout << "Boarding queue after 3 passengers entered : ";
    print(flight1);

    boardFlight(flight1);
    std::cout << "Boarding queue after 1 passenger boarded : ";
    print(flight1);

    enterQueue(flight1, "Sania", "Business");
    std::cout << "Boarding queue after 1 passenger entered with ticket : ";
    print(flight1);

    boardFlight(flight1);
    std::cout << "Boarding queue after 1 passenger boarded : ";
    print(flight1);

    // Now, let’s say, Sachin realized that he’s entered into wrong queue and wants to get out.
    remove(flight1);
    std::cout << "Boarding queue after Sachin got out : ";
    print(flight1);
}
