#ifndef SIGNALS_H_01e4f5c85821dd19c257fd0629349354
#define SIGNALS_H_01e4f5c85821dd19c257fd0629349354

#include <map>
#include <vector>
#include <functional>

template<typename... Args>
class Signal {
    using CallbackId_t = size_t;
    std::vector<std::function<void(Args...)>> slots;

public:

    Signal() {}
    ~Signal() = default;

    CallbackId_t connect(const std::function<void(Args...)>&& funct) {
        slots.emplace_back(funct);
        return slots.size() - 1;
    }

    CallbackId_t connect(const std::function<void(Args...)>& funct) {
        slots.emplace_back(funct);
        return slots.size() - 1;
    }

    void emit(Args&&... args) const {
        for (const auto &func : slots) {
            func(std::forward<Args>(args)...);
        }
    }

    void discounnectAll() {
        slots.clear();
    }

    void disconnect(const CallbackId_t callback_id) {
        if (callback_id < slots.size()) {
            slots.erase(callback_id);
        }
    }

    bool isConnected(const CallbackId_t callback_id) const {
        return callback_id < slots.size();
    }

};

#endif