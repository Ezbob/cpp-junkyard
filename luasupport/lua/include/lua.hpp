// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <iostream>
#include <functional>

const int STACK_TOP = -1;

/*
 * RAII for a lua state
 */
class LuaRAIIState {

public:
    LuaRAIIState() {
        m_state = luaL_newstate();
    }

    ~LuaRAIIState() {
        lua_close(m_state);
    }

    lua_State *ptr() {
        return m_state;
    }

    operator lua_State *() {
        return m_state;
    }

    bool checkError(int return_code) {
        if (return_code != LUA_OK) {
            std::string errormsg = lua_tostring(m_state, -1);
            std::cout << errormsg << std::endl;
            return false;
        }
        return true;
    }

    void requestGlobal(const std::string name) {
        lua_getglobal(m_state, name.c_str());
    }

    void requestGlobal(const char *name) {
        lua_getglobal(m_state, name);
    }

    void push(double val) {
        lua_pushnumber(m_state, val);
    }

    void push(int val) {
        lua_pushnumber(m_state, val);
    }

    void push(bool val) {
        lua_pushboolean(m_state, val);
    }

    void push(const char *val) {
        lua_pushstring(m_state, val);
    }
    
    void push(const std::string val) {
        lua_pushstring(m_state, val.c_str());
    }

    bool hasNumber(int index = STACK_TOP) {
        return lua_isnumber(m_state, index);
    }

    double getNumber(int index = STACK_TOP) {
        return (double) lua_tonumber(m_state, index);
    }

    bool hasTable(int index = STACK_TOP) {
        return lua_istable(m_state, index);
    }

    void requestFromTable(int table_index = (STACK_TOP - 1)) {
        lua_gettable(m_state, table_index);
    }

    bool hasString(int index = STACK_TOP) {
        return lua_isstring(m_state, index);
    }

    std::string getString(int index = STACK_TOP) {
        return lua_tostring(m_state, index);
    }

    bool hasBool(int index = STACK_TOP) {
        return lua_isboolean(m_state, index);
    }

    bool hasFunction(int index = STACK_TOP) {
        return lua_isfunction(m_state, index);
    }

    bool getBool(int index = STACK_TOP) {
        return lua_toboolean(m_state, index);
    }

    void pop(int number_of_elements = 1) {
        lua_pop(m_state, number_of_elements);
    }

    int stackSize() {
        return lua_gettop(m_state);
    }

    void clearStack() {
        lua_pop(m_state, lua_gettop(m_state));
    }

    void registerFunction(std::string functionName, int (*function)(lua_State *)) {
        lua_register(m_state, functionName.c_str(), function);
    }

    void registerFunction(const char *functionName, int (*function)(lua_State *)) {
        lua_register(m_state, functionName, function);
    }

private:
    lua_State *m_state;
};