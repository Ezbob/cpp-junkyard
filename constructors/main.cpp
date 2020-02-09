#include <iostream>
#include <algorithm>

/*
 * Class A here implements the Rule of Five for a class containing
 * non-trivial member (this being the heap allocated int array type 'arr').
 * The Rule of Five ensures that pointers are not shared between instances,
 * which can lead to memory errors due to a break-down of class encapsulation.
 *
 */
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
    
    /**
     * 1. Non-default destructor implementation. 
     */
    ~A()
    {
        if (arr)
        {
            std::cout << "destroying\n";
            delete[] arr;
        }
    }

    /**
     * 2. Copy constructor: makes a new copy of an already existing instance 
     */
    A(A const &other) : count(other.count), arr(new int[other.count])
    {
        std::cout << "copy construct\n";
        std::copy(other.arr, other.arr + count, arr);
    }
    
    /*One could also have wrote:
    *
    * A(A const&) = default;
    *
    * This would explicitly state that we want the default behaviour of shallow copy, copy constructor
    * to be made. Another options would be to delete the function:
    *
    * A(A const&) = delete;
    * 
    * These tricks holds for the other Rule of Five subjects.
    */

    /** 
     * 3. Copy assignment. Note the difference with the copy constructor; the other instance
     * can be the same instance as the class itself since you can do something like 'A a(10); a = a;'
     */
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

    /**
     * 4. Move construction. This is used when 'this' instance is constructed by a temporary or
     * by a std::move of some other instance. These other instances are also called 'rvalues'
     */
    A(A &&other) : count(other.count)
    {
        std::cout << "move construct\n";
        delete[] arr;
        arr = other.arr;
        other.arr = nullptr;
    }

    /**
     * 5. Move assignment operator. Does the same thing has the move constructor except for
     * both instances has been initialized.
     */
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
