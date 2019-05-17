#include <iostream>

template<typename Printable>
struct RepeatPrint : Printable {

    explicit RepeatPrint(Printable const &printable) : Printable(printable) {}
    void repeat(unsigned int n) const {
        while(n-- > 0) {
            this->print(); // this-> is needed here because compiler does not know where print is otherwise
        }
    }
};


class Name {

    std::string firstName_;
    std::string lastName_;

public: 
    Name(std::string firstName, std::string lastName)
        : firstName_(std::move(firstName))
        , lastName_(std::move(lastName)) {}

    void print() const {
        std::cout << lastName_ << ", " << firstName_ << std::endl;
    }

};

struct ITask {
    //virtual ~ITask() = 0;
    virtual void execute() = 0;
    virtual std::string getName() = 0;
};

template<typename T>
struct LoggingTask : public T { // Loggin mixin for tasks

    void execute() {
        std::cout << "LOG: Task is starting - " << this->getName() << std::endl;
        T::execute();
        std::cout << "LOG: Task is complete - " << this->getName() << std::endl; 
    }
};

template<typename T>
struct TaskAdapter : public ITask, public T { // glues the ITask interface and mixin tasks together

    virtual void execute() {
        T::execute();
    }

    virtual std::string getName() {
        return T::getName();
    }
};

class MyTask { // my special task

public:

    void execute() {
        std::cout << "Doing some work" << std::endl;
    }

    std::string getName() {
        return "Name";
    }

};

using Task_t = TaskAdapter<LoggingTask<MyTask>>;

/**
 * This task is only usable with
 * the task adapter
 */
void task_api_function(ITask *t) {
    t->execute();
}

int main() {

    Name anders("Anders", "Busch");

    anders.print();
    RepeatPrint a(anders);
    a.repeat(10);


    Task_t task;

    task.execute();


    task_api_function(&task);

    return 0;
}
