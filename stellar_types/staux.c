#include "staux.h"

int staux_register_type(lua_State *L) {
    if (lua_type(L, lua_upvalueindex(1)) == LUA_TSTRING) {
        const char* type_value = lua_tostring(L, lua_upvalueindex(1));
        const char* field_name = lua_tostring(L, -4);
        if (strcmp(type_value, STELLAR_TSTRING) == 0) {
            if (lua_type(L, -3) != LUA_TSTRING) {
                luaL_error(L, "Expected a string for field \'%s\'", field_name);
            }
        } else if (strcmp(type_value, STELLAR_TNUMBER) == 0) {
            if (lua_type(L, -3) != LUA_TNUMBER) {
                luaL_error(L, "Expected a number for field \'%s\'", field_name);
            }
        } else if (strcmp(type_value, STELLAR_TBOOLEAN) == 0) {
            if (lua_type(L, -3) != LUA_TBOOLEAN) {
                luaL_error(L, "Expected a boolean for field \'%s\'", field_name);
            }
        } else if (strcmp(type_value, STELLAR_TINTEGER) == 0) {
            if (lua_type(L, -3) != LUA_TNUMBER || lua_tointeger(L, -3) != lua_tonumber(L, -3)) {
                luaL_error(L, "Expected an integer for field \'%s\'", field_name);
            }
        } else if (strcmp(type_value, STELLAR_TFLOAT) == 0) {
            if (lua_type(L, -3) != LUA_TNUMBER || lua_tointeger(L, -3) == lua_tonumber(L, -3)) {
                luaL_error(L, "Expected a float (decimal) for field \'%s\'", field_name);
            }
        } else if (strcmp(type_value, STELLAR_TARRAY) == 0) {
            if (lua_type(L, -3) != LUA_TTABLE) {
                luaL_error(L, "Expected an array (table) for field '%s'", field_name);
            }
            /* Check if all keys are integers (array-like table) */
            lua_pushnil(L);
            while (lua_next(L, -4)) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                luaL_error(L, "Expected array (table with integer keys) for field '%s'", field_name);
            }
            lua_pop(L, 1); /* remove value, keep key for next iteration */
            }
        } else {
            luaL_error(L, "Unsupported type \'%s\' for field in type \'%s\'", type_value, field_name);
        }
    } else if (lua_type(L, lua_upvalueindex(1)) == LUA_TTABLE) {
        if (lua_getmetatable(L, -3) == 0) {
            luaL_error(L, "Expected a metatable-based object for field '%s'", lua_tostring(L, -4));
        }
        if (!lua_rawequal(L, -1, lua_upvalueindex(1))) {
            luaL_error(L, "Wrong type for field \'%s\'", lua_tostring(L, -5));
        }
        lua_pop(L, 1); /* remove metatable */
    }
    return 0;
}