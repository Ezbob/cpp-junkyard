#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

/**
 *  filter function that can take any type of member and any type of collection that has 
 *  a) a push_back method and b) uses a template with an allocator as the second template argument;
 *  and filter a collection given some predicate function
 */
template<typename Member_t, template<typename, typename Allocate_t = std::allocator<Member_t>> class Container_t>
Container_t<Member_t> filter(Container_t<Member_t> const &collection, std::function<bool(Member_t const &)> predicate_function) {
    Container_t<Member_t> results;

    for ( Member_t const &member : collection ) {
        if ( predicate_function(member) ) {
            results.push_back(member);
        }
    }

    return results;
}

struct AStruct {
    int a;
    std::string name;
};


int main() {

    std::cout << "it compiles!" << std::endl;

    std::vector<AStruct> a;

    a.push_back({ 10, "okay" });
    a.push_back({ 12, "madness" });
    a.push_back({ 9, "cool" });
    a.push_back({ 9, "awesome" });

    std::vector<AStruct> filtered = filter<AStruct>( a, [](AStruct const & ref) { return ref.a == 9; } ); 

    for ( auto &member : filtered )
        std::cout << member.name << std::endl;

    return 0;
}

