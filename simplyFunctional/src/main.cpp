#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>


template<typename Container_t, typename UnaryPredicate_t>
Container_t filter(Container_t const &collection, UnaryPredicate_t &&predicate_function) {
    Container_t results;
    std::copy_if(collection.begin(), collection.end(), std::back_inserter(results), predicate_function);
    return results;
}

template<typename Container_t, typename UnaryOperator_t>
Container_t map(Container_t const &collection, UnaryOperator_t &&map_function) {
    Container_t results;
    std::transform(collection.begin(), collection.end(), std::back_inserter(results), map_function);
    return results;
}

template<typename Container_t, typename UnaryPredicate_t>
Container_t filter(Container_t const &collection, UnaryPredicate_t &predicate_function) {
    Container_t results;
    std::copy_if(collection.begin(), collection.end(), std::back_inserter(results), predicate_function);
    return results;
}

template<typename Container_t, typename UnaryOperator_t>
Container_t map(Container_t const &collection, UnaryOperator_t &map_function) {
    Container_t results;
    std::transform(collection.begin(), collection.end(), std::back_inserter(results), map_function);
    return results;
}

struct AStruct {
    int a;
    std::string name;
};

template<typename T>
struct PredicatorFunctor {

    PredicatorFunctor() {}
    virtual ~PredicatorFunctor() = default; 

    bool operator() (T const &r) {
        return r.a == 10;
    }
};

template<typename T>
struct MutationFunctor {
    T operator() (T r) {
        r.a = 37;
        return r;
    }
};

int main() {

    std::vector<AStruct> a = {
        AStruct{ 10, "okay" },
        AStruct{ 12, "madness" },
        AStruct{ 9, "cool" },
        AStruct{ 10, "funny" },
        AStruct{ 9, "awesome" }
    };

    auto filtered = filter(a, [](AStruct const &ref) { return ref.a == 9; } ); 

    for ( auto &member : filtered )
        std::cout << member.name << std::endl;

    auto pred = PredicatorFunctor<AStruct>();

    auto filtered2 = filter(a, pred);

    for ( auto &member : filtered2 )
        std::cout << member.name << std::endl;

    auto mapped = map(filter(a, pred), [](AStruct a) { 
        a.a = 42;
        return a;
    });

    for (auto &member : mapped) {
        std::cout << member.name << ", " << member.a << std::endl;
    }

    auto mapped2 = map(filter(a, pred), MutationFunctor<AStruct>());

    for (auto &member : mapped2) {
        std::cout << member.name << ", " << member.a << std::endl;
    }

    return 0;
}

