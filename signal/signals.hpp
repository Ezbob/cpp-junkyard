#ifndef SIGNALS_H_01e4f5c85821dd19c257fd0629349354
#define SIGNALS_H_01e4f5c85821dd19c257fd0629349354

#include <map>
#include <vector>
#include <functional>

template<typename... Args>
class SignalSlot {
    std::map<std::string, std::map<uint64_t, std::function<void(Args...)>>> slots;

public:

    SignalSlot() {}
    ~SignalSlot() = default;

    uint64_t bind(const std::string name, const std::function<void(Args...)>&& funct) {
        static uint64_t id_counter = 0;
        slots[name].emplace(std::pair<uint64_t, std::function<void(Args...)>>(id_counter, funct));
        return id_counter++;
    }

    void emit(const std::string name, Args&&... args) const {
        auto it = slots.find(name);
        if (it != slots.end()) {
            auto callback_map = it->second;
            for (auto &item : callback_map) {
                item.second(std::forward<Args>(args)...);
            }
        }
    }

    void unbindAll(const std::string name) {
        slots.erase(name);
    }

    void unbind(const std::string name, const uint64_t callback_id) {
        auto it = slots.find(name);

        if (it != slots.end()) {
            auto &callback_map = it->second;
            callback_map.erase(callback_id);
        }
    }

};

#endif