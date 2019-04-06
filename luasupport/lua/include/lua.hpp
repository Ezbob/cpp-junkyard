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
#include <cstddef>
#include <array>

const int STACK_TOP = -1;

bool LuaCheckError(lua_State *s, int return_code) {
    if (return_code != LUA_OK) {
        std::string errormsg = lua_tostring(s, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

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

    void addGlobal(const std::string name) {
        lua_setglobal(m_state, name.c_str());
    }

    void addGlobal(const char *name) {
        lua_setglobal(m_state, name);
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

    void push(int (*function)(lua_State *)) {
        lua_pushcfunction(m_state, function);
    }

    void push(void) {
        lua_pushnil(m_state);
    }

    void pushCopyOf(int index) {
        lua_pushvalue(m_state, index);
    }

    bool hasNumber(int index = STACK_TOP) {
        return lua_isnumber(m_state, index);
    }

    int openTable() {
        lua_newtable(m_state);
        int tableref = lua_gettop(m_state);
        return tableref;
    }

    template<typename T>
    void addTableMember(int tableIndex, const std::string name, T value) {
        push(name);
        push(value);
        lua_settable(m_state, tableIndex);
    }

    template<typename T>
    void addTableMember(int tableIndex, const char *name, T value) {
        push(name);
        push(value);
        lua_settable(m_state, tableIndex);
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

    bool callFunction(int numberOfInputArgs, int numberOfReturnValues, int errorHandlerIndex = 0) {
        return checkError(lua_pcall(m_state, numberOfInputArgs, numberOfReturnValues, errorHandlerIndex));
    }

private:
    lua_State *m_state;
};

struct LuaFunctionArg {
    enum {
        STRING,
        INT,
        DOUBLE,
        BOOL
    } type;
    union {
        char *strval;
        int intval;
        double doubleval;
        bool boolval;
    };

    void pushToStack(lua_State *L) {
        switch(type) {
            case LuaFunctionArg::STRING:
                lua_pushstring(L, strval);
                break;
            case LuaFunctionArg::INT:
                lua_pushinteger(L, intval);
                break;
            case LuaFunctionArg::DOUBLE:
                lua_pushnumber(L, doubleval);
                break;
            case LuaFunctionArg::BOOL:
                lua_pushboolean(L, boolval);
                break;
        }
    }
};


template<int nInputArgs = 0, int nOutputArgs = 0, int faultHandlerIndex = 0>
class LuaTableFunction {

public:
    bool operator() (std::array<LuaFunctionArg, nInputArgs> *inputArgs = nullptr, std::function<void (lua_State *)> *outputExtractor = nullptr) {
        lua_pushstring(m_state, m_name);
        lua_gettable(m_state, (STACK_TOP - 1));
        if ( lua_isfunction(m_state, STACK_TOP) ) {

            if ( inputArgs != nullptr ) {
                for (auto l : (*inputArgs)) {
                    l.pushToStack(m_state);
                }
            }

            if ( LuaCheckError(m_state, lua_pcall(m_state, m_input, m_output, m_faultHandler_index)) ) {
                if ( outputExtractor != nullptr ) {
                    (*outputExtractor)(m_state);
                }
            } else {
                lua_pop(m_state, 1);
                return false;
            }
        } else {
            lua_pop(m_state, 1);
            return false;
        }
        lua_pop(m_state, 1);
        return true;
    }

    void setMembers(lua_State *s, const char *name, const char *table_name) {
        m_state = s;
        m_name = name;
        m_table_name = table_name;
    }

private:
    int m_input = nInputArgs;
    int m_output = nOutputArgs;
    int m_faultHandler_index = faultHandlerIndex;
    const char *m_name;
    const char *m_table_name;
    lua_State *m_state;
};

class LuaTableConverter {

private:
    lua_State *m_state;
    int m_table_index = (STACK_TOP - 1);
    const char *m_table_name = "";

public:
    bool readFromGlobal(lua_State *luaState, const char *tableName) {
        m_table_name = tableName;
        m_state = luaState;

        lua_getglobal(m_state, m_table_name);
        if ( lua_istable(m_state, STACK_TOP) ) {
            LuaTableMappings();
            return true;
        }
        return false;
    }

    explicit LuaTableConverter() = default;

protected:
    virtual void LuaTableMappings() {}

    void map(std::string &s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isstring(m_state, STACK_TOP) ) {
            s = lua_tostring(m_state, STACK_TOP);
        }

        lua_pop(m_state, 1);
    }

    void map(const char *&s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isstring(m_state, STACK_TOP) ) {
            s = lua_tostring(m_state, STACK_TOP);
        }

        lua_pop(m_state, 1);
    }

    template<typename T>
    void map(T &s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isnumber(m_state, STACK_TOP) ) {
            s = lua_tonumber(m_state, STACK_TOP);
        }

        lua_pop(m_state, 1);
    }

    void required_map(std::string &s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isstring(m_state, STACK_TOP) ) {
            s = lua_tostring(m_state, STACK_TOP);
            lua_pop(m_state, 1);
        } else {
            lua_pop(m_state, 1);
            throw std::out_of_range(luaName);
        }
    }

    void required_map(const char *&s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isstring(m_state, STACK_TOP) ) {
            s = lua_tostring(m_state, STACK_TOP);
            lua_pop(m_state, 1);
        } else {
            lua_pop(m_state, 1);
            throw std::out_of_range(luaName);
        }

    }

    template<typename T>
    void required_map(T &s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isnumber(m_state, STACK_TOP) ) {
            s = lua_tonumber(m_state, STACK_TOP);
            lua_pop(m_state, 1);
        } else {
            lua_pop(m_state, 1);
            throw std::out_of_range(luaName);
        }
    }

    template<int inputArgs, int outputArgs>
    void required_map(LuaTableFunction<inputArgs, outputArgs> &s, const char *luaName) {

        lua_pushstring(m_state, luaName);
        lua_gettable(m_state, (STACK_TOP - 1));

        if ( lua_isfunction(m_state, STACK_TOP) ) {
            s.setMembers(m_state, luaName, m_table_name);
            lua_pop(m_state, 1);
        } else {
            lua_pop(m_state, 1);
            throw std::out_of_range(luaName);
        }
    }


};
