#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cstddef>
#include <chrono>

template<typename T>
class SafeQueue {
public:
    SafeQueue(void) 
        : m_queue() 
        , m_mutex()
        , m_condition() {}

    ~SafeQueue(void) {}

    void offer(T element) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(element);
        m_condition.notify_one();
    }

    T poll(void) {
        std::unique_lock<std::mutex> synch_lock(m_mutex);
        m_condition.wait(synch_lock, [this] {
            return !m_queue.empty();
        });
        T value = m_queue.front();
        m_queue.pop();
        return value;
    }

    const T peek(void) {
        std::unique_lock<std::mutex> synch_lock(m_mutex);
        m_condition.wait(synch_lock, [this] {
            return !m_queue.empty();
        });
        return m_queue.front();
    }

    uint64_t size() {
        return m_queue.size();
    }

    bool empty() {
        return m_queue.empty();
    }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
};

template<typename ArgType>
struct Task {
    std::vector<ArgType> args;
    enum class Type {
        SOMETHING
    } type;
};

void fun1(SafeQueue<float> &q) {
    while(!q.empty()) {
        std::cout << "Thread 1 executing\n";
        q.poll();
    }
}

void fun2(SafeQueue<float> &q) {
    while(!q.empty()) {
        std::cout << "Thread 2 executing\n";
        q.poll();
    }
}


int main(int argc, char const *argv[])
{
    SafeQueue<float> sq;

    sq.offer(2.3);
    sq.offer(2.1);
    sq.offer(2.7);
    sq.offer(3.1);
    sq.offer(2.7);
    sq.offer(3.1);

    std::thread t1(fun1, std::ref(sq));
    std::thread t2(fun2, std::ref(sq));

    t1.detach();
    t2.detach();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "final size of the queue " << sq.size() << std::endl;
    return 0;
}
