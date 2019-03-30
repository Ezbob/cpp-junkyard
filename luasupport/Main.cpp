#include <iostream>
#include <string>
#include "lua.hpp"

struct Player {
    std::string title;
    std::string name;
    int level;
};

int lua_HostFunction(lua_State * L) {

    if ( lua_gettop(L) < 2 ) {
        std::cerr << "Error: Not enough arguments provided to HostFunction. "
        "Expected 2 got " << lua_gettop(L) << "." << std::endl;
        lua_pushnil(L);
        return 1;
    }

    double a = (double)lua_tonumber(L, 1);
    double b = (double)lua_tonumber(L, 2);

    std::cout << "HOST FUNCTION CALLed with a: " << a << " b: " << b << std::endl;

    double res = a * b;
    lua_pushnumber(L, res);
    return 1;
}

int main(int argc, char **argv) {

    if ( argc < 2 ) {
        std::cerr << "Error: Expected first argument to be path to script" << std::endl;
        exit(1);
    }

    Player player;

    char *filename = argv[1];

    LuaRAIIState L;

    luaL_openlibs(L);

    L.registerFunction("HostFunction", lua_HostFunction);

    if ( L.checkError(luaL_dofile(L, filename)) ) {

        L.requestGlobal("AddStuff");

        if ( L.hasFunction() ) {

            L.push(32);
            L.push(20);

            if (L.checkError(lua_pcall(L, 2, 1, 0))) {
                std::cout << "Got result from lua: " << L.getNumber() << std::endl;
            }

            L.clearStack();
        }

        L.requestGlobal("DoAThing");

        if ( L.hasFunction() ) {

            L.push(10);
            L.push(10);

            if (L.checkError(lua_pcall(L, 2, 1, 0))) {
                std::cout << "Got result from lua: " << L.getNumber() << std::endl;
            }

           L.clearStack();
        }


         /*
            L.push("Name");
            L.requestFromTable();
            if ( L.hasString() ) {
                player.name = L.getString();
            }
            L.pop();

            L.push("Title");
            L.requestFromTable();
            if ( L.hasString() ) {
                player.title = L.getString();
            }
            L.pop();

            L.push("Level");
            L.requestFromTable();
            if ( L.hasNumber() ) {
                player.level = L.getNumber();
            }
            L.pop();

            std::cout << 
                player.name << 
                ", " << 
                player.title <<
                ", (level " <<
                player.level <<
                ")" << 
                std::endl;

            */
    }

    return 0;
}