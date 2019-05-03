#ifndef SIGNALS_H_01e4f5c85821dd19c257fd0629349354
#define SIGNALS_H_01e4f5c85821dd19c257fd0629349354

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <utility>


class SignalSlot {

    std::map<std::string, std::vector< std::function<void()> > > slots;

public:

    SignalSlot() {}
    ~SignalSlot() = default;

    template<typename F, typename... Args>
    void bind(std::string name, F&& funct, Args&&... args) {
        auto it = slots.find(name);
        auto bound_function = std::bind(std::forward<F>(funct), std::forward<Args>(args)...);

        if (it != slots.end()) {
            auto slot = it->second;
            slot.emplace_back([bound_function]() { bound_function(); });
        } else {
            std::vector<std::function<void()>> v { bound_function };
            slots.emplace(std::make_pair(name, v));
        }
    }

    void emit(std::string name) {
        auto it = slots.find(name);
        if (it != slots.end()) {
            auto functions = it->second;
            for (auto &func : functions) {
                func();
            }
        }
    }
};

#endif