#ifndef SIGNALS_H_01e4f5c85821dd19c257fd0629349354
#define SIGNALS_H_01e4f5c85821dd19c257fd0629349354

#include <map>
#include <vector>
#include <functional>

template<typename... Args>
class SignalSlot {

    std::map<std::string, std::vector<std::function<void(Args...)>>> slots;

public:

    SignalSlot() {}
    ~SignalSlot() = default;

    void bind(const std::string name, const std::function<void(Args...)>&& funct) {
        slots[name].emplace_back(funct);
    }

    void emit(const std::string name, Args&&... args) const {
        auto it = slots.find(name);
        if (it != slots.end()) {
            auto functions = it->second;
            for (auto &func : functions) {
                func(std::forward<Args>(args)...);
            }
        }
    }
};

#endif