#include <iostream>
#include <string>
#include "lua.hpp"

struct Player {
    std::string title;
    std::string name;
    int level;
};

int main(int argc, char **argv) {

    if ( argc < 2 ) {
        std::cerr << "Error: Expected first argument to be path to script" << std::endl;
        exit(1);
    }

    Player player;

    char *filename = argv[1];

    LuaRAIIState L;

    luaL_openlibs(L);

    if ( L.checkError(luaL_dofile(L, filename)) ) {

        L.requestGlobal("AddStuff");

        if ( L.hasFunction() ) {

            L.push(32);
            L.push(20);

            if (L.checkError(lua_pcall(L, 2, 1, 0))) {
                std::cout << "Got result from lua: " << L.getNumber() << std::endl;
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
    }

    return 0;
}