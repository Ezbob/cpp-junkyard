#ifndef SIGNALS_H_01e4f5c85821dd19c257fd0629349354
#define SIGNALS_H_01e4f5c85821dd19c257fd0629349354

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <utility>

template<typename... Args>
class SignalSlot {
    using Function_t = std::function<void(Args...)>;
    std::map<std::string, std::vector<Function_t>> slots;

public:

    SignalSlot() {}
    ~SignalSlot() = default;

    void bind(std::string name, Function_t&& funct) {
        auto it = slots.find(name);

        if (it != slots.end()) {
            auto slot = it->second;
            slot.emplace_back(std::forward<Function_t>(funct));
        } else {
            std::vector<Function_t> v { std::forward<Function_t>(funct) };
            slots.emplace(std::make_pair(name, v));
        }
    }

    void emit(std::string name, Args&&... args) {
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