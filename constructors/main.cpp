#include <iostream>
#include <algorithm>

class A
{
private:
    int count = 0;
    int *arr = nullptr;

public:
    explicit A(const int count) : count(count)
    {
        arr = new int[count];
    }
    ~A()
    {
        if (arr)
        {
            std::cout << "destroying\n";
            delete[] arr;
        }
    }

    A(A const &other) : count(other.count), arr(new int[other.count])
    {
        std::cout << "copy construct\n";
        std::copy(other.arr, other.arr + count, arr);
    }

    A &operator=(A const &other)
    {
        std::cout << "copy assign\n";
        if (this != &other)
        {
            int *narr = new int[other.count];
            delete[] arr;

            arr = narr;
            count = other.count;
            std::copy(other.arr, other.arr + count, arr);
        }
        return *this;
    }

    A(A &&other) : count(other.count)
    {
        std::cout << "move construct\n";
        delete[] arr;
        arr = other.arr;
        other.arr = nullptr;
    }

    A &operator=(A &&other)
    {
        std::cout << "move assign\n";
        if (this != &other)
        {
            delete[] arr; // remove our memory (otherwise we will leak)

            count = other.count;
            arr = other.arr; // pointer is now copied

            other.arr = nullptr; // clear the other object's pointer otherwise it will free it in it's destructor
        }
        return *this;
    }
};

int main()
{
    A a(20);
    A c(20);


    A b = a; // copy construct

    a = c; // copy assign as 'a' is already constructed

    c = A(20); // rhs is a temporay 'rvalue'; so it's a move assignment

    A d = std::move(c); // std::move forces c to be moved and d is constructed in this expression so it's a move constructor

    return 0;
}
