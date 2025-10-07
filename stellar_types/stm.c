#include "stm.h"

int stm_new(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_getfield(L, 1, STELLAR_VALIDATORS);
    int validators_index = lua_gettop(L);

    lua_newtable(L);
    int instance_index = lua_gettop(L);

    lua_pushvalue(L, 1);
    lua_setmetatable(L, instance_index);

    lua_pushnil(L);
    while (lua_next(L, 2) != 0) {
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -2);
        lua_settable(L, instance_index);
        lua_pop(L, 1);
    }

    lua_getfield(L, 1, STELLAR_DEFAULTS);
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        const char* field = lua_tostring(L, -2);
        lua_getfield(L, instance_index, lua_tostring(L, -2));
        if (lua_isnil(L, -1) && !lua_isnil(L, -2)) {
            lua_pushvalue(L, -2);
            lua_setfield(L, instance_index, field);
        }
        lua_pop(L, 2);
    }
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
    lua_pushvalue(L, -1);

    lua_getfield(L, -1, "__extra_validators");
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