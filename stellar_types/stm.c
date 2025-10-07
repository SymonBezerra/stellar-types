#include "stm.h"

int stm_new(lua_State *L) {
    lua_getfield(L, 1, STELLAR_CLASS);
    lua_pushstring(L, STELLAR_TYPES_MODULE);
    if (!lua_compare(L, -1, -2, LUA_OPEQ)) {
        luaL_error(L, "Class is not a StellarTypes class");
    }
    luaL_checktype(L, 2, LUA_TTABLE);

    lua_getfield(L, 1, STELLAR_VALIDATORS);
    int validators_index = lua_gettop(L);

    lua_getfield(L, 1, STELLAR_DEFAULTS);
    int defaults_index = lua_gettop(L);

    lua_newtable(L);
    int instance_index = lua_gettop(L);

    lua_pushvalue(L, 1);
    lua_setmetatable(L, instance_index);

    lua_pushnil(L);
    while (lua_next(L, 2) != 0) {
        const char* name = lua_tostring(L, -2);
        if (!lua_isnil(L, -1)) {
            lua_pushstring(L, name);
            lua_pushvalue(L, -2);
            lua_settable(L, instance_index);
        } else {
            lua_getfield(L, defaults_index, name);
            if (!lua_isnil(L, -1)) {
                lua_pushstring(L, name);
                lua_pushvalue(L, -2);
                lua_settable(L, instance_index);
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    lua_getfield(L, 1, STELLAR_VALIDATORS);
    lua_pushnil(L);
    while(lua_next(L, -2) != 0) {
        const char* name = lua_tostring(L, -2);
        lua_getfield(L, instance_index, name);
        lua_getfield(L, defaults_index, name);
        if (!lua_isnil(L, -1) && lua_isnil(L, -2)) {
            lua_pushstring(L, name);
            lua_pushvalue(L, -2);
            lua_settable(L, instance_index);
        }
        lua_pop(L, 3);
    }
    lua_pop(L ,1);
    return 1;
}

int stm_newindex(lua_State *L) {
    const char *key = luaL_checkstring(L, 2);

    lua_getmetatable(L, 1);
    lua_getfield(L, -1, STELLAR_VALIDATORS);
    lua_getfield(L, -1, key);
    if (lua_isfunction(L, -1)) {
        lua_pushvalue(L, 3);
        lua_pushvalue(L, 2);
        lua_call(L, 2, 1);
        if (!lua_toboolean(L, -1)) {
            return 0;
        }
    }
    lua_pop(L, 2);
    lua_getmetatable(L, 1);

    lua_getfield(L, -1, STELLAR_EXTRA_VALIDATORS);
    lua_getfield(L, -1, key);
    int valid = TRUE;
    if (!lua_isnil(L, -1)) {
        lua_pushvalue(L, 3);
        lua_call(L, 1, 1);
        if (!lua_isboolean(L, -1) || lua_isnil(L, -1)) {
            stm_error("User-defined validation did not return a boolean for field", key);
            stm_warning("User-defined validation did not return a boolean for field", key);
            valid = FALSE;
        } else if (!lua_toboolean(L, -1)) {
            lua_getfield(L, -3, STELLAR_DEFAULTS);
            lua_getfield(L, -1, key);
            if (!lua_isnil(L, -1)) {
                stm_setdefault(L, 1);
                return 0;
            } else {
                lua_pop(L, 2);
                stm_error("User-defined validation failed for field", key);
                stm_warning("User-defined validation failed for field", key);
                valid = FALSE;
            }
        }
        lua_pop(L, 2);
    }
    lua_pop(L, 2);
    if (valid) {
        stm_setvalue(L);
    }
}