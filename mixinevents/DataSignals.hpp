
#ifndef _HEADER_FILE_DataSignals_20190927215434_
#define _HEADER_FILE_DataSignals_20190927215434_

#include "Signal.hpp"

template<typename Derived_t>
class DataSignals {

    struct Signals {
        Signal<const Derived_t &> ready;
    } __signals__;

protected:
    void _emit_ready(const Derived_t &r) {
        __signals__.ready.emit(r);
    }

    void _emit_ready(const Derived_t *r) {
        __signals__.ready.emit(*r);
    }

public:
    DataSignals() {}
    virtual ~DataSignals() = default;

    void on_ready(std::function<void (const Derived_t &)> &f) {
        __signals__.ready.connect(f);
    }

    void on_ready(std::function<void (const Derived_t &)> &&f) {
        __signals__.ready.connect(f);
    }
};

#endif