#include <iostream>

template <typename T>
struct singly_ll_node
{
    T data;
    singly_ll_node *next;
};

template <typename T>
class singly_ll
{
public:
    using node = singly_ll_node<T>;
    using node_ptr = node *;

private:
    node_ptr head;
    node_ptr last;
    size_t n;

public:
    size_t size() const
    {
        return size;
    }

    T &back()
    {
        return last->data;
    }

    void push_front(const T &val)
    {
        auto new_node = new node{val, NULL};
        if (head != NULL)
            new_node->next = head;
        else
            last = new_node;

        head = new_node;
        n++;
    }

    void pop_front()
    {
        auto first = head;
        head = head->next;
        if (head == NULL)
            last = NULL;
        delete first;
        n--;
    }

    struct singly_ll_iterator
    {
    private:
        node_ptr ptr;

    public:
        singly_ll_iterator(node_ptr p) : ptr(p)
        {
        }

        T &operator*()
        {
            return ptr->data;
        }

        node_ptr get()
        {
            return ptr;
        }

        singly_ll_iterator &operator++() // pre-increment
        {
            ptr = ptr->next;
            return *this;
        }

        singly_ll_iterator operator++(int) // post-increment
        {
            singly_ll_iterator result = *this;
            ++(*this);
            return result;
        }

        friend bool operator==(const singly_ll_iterator &left, const singly_ll_iterator &right)
        {
            return left.ptr == right.ptr;
        }

        friend bool operator!=(const singly_ll_iterator &left, const singly_ll_iterator &right)
        {
            return left.ptr != right.ptr;
        }
    };

    singly_ll_iterator begin()
    {
        return singly_ll_iterator(head);
    }

    singly_ll_iterator end()
    {
        return singly_ll_iterator(NULL);
    }

    singly_ll_iterator begin() const
    {
        return singly_ll_iterator(head);
    }

    singly_ll_iterator end() const
    {
        return singly_ll_iterator(NULL);
    }

    void push_back(const T &val)
    {
        auto new_node = new node{val, NULL};
        if (head != NULL)
            last->next = new_node;
        else
            head = new_node;

        last = new_node;
        n++;
    }

    void pop_back()
    {
        auto it = begin();
        while (it.get()->next != last)
            it++;
        auto curLast = last;
        last = it.get();
        last->next = NULL;
        n--;
        delete curLast;
    }

    singly_ll() = default;

    singly_ll(const singly_ll<T> &other) : head(NULL), last(NULL), n(0)
    {
        for (const auto &i : other)
            push_back(i);
    }

    singly_ll(const std::initializer_list<T> &ilist) : head(NULL), last(NULL), n(0)
    {
        for (const auto &i : ilist)
            push_back(i);
    }
};

int main()
{
    singly_ll<int> sll = {1, 2, 3};
    sll.push_back(4);
    sll.push_front(0);

    std::cout << "First list : ";
    for (auto i : sll)
        std::cout << i << " ";
    std::cout << std::endl;

    auto sll2 = sll;
    sll2.pop_back();
    std::cout << "Second list after copying from first list and deleting last element : ";
    for (auto i : sll2)
        std::cout << i << " "; // Prints 0 1 2 3
    std::cout << std::endl;

    std::cout << "First list after copying and deleting last element from copied list remains unchanged – confirming deep copy : ";
    for (auto i : sll)
        std::cout << i << " "; // Prints 0 1 2 3 4
    std::cout << std::endl;
}
