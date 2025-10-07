#ifndef STM_H
#define STM_H

#include <stdio.h>
#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>

#include "sto.h"

/* Stellar Types module functions */

#define stm_setdefault(L) \
    lua_pushvalue(L, 2); \
    lua_pushvalue(L, -2); \
    lua_rawset(L, 1); \
    return 0;

#define stm_setvalue(L) \
    lua_pushvalue(L, 2); \
    lua_pushvalue(L, 3); \
    lua_rawset(L, 1); \
    return 0;

#define stm_warning(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "warnings"); \
    if ((lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1)) || lua_type(L, -1) == LUA_TNIL) { \
        fprintf(stderr, "%s: %s, \'%s\'\n", STELLAR_WARNING, msg, field); \
        return 0; \
    } \
    lua_pop(L, 2);

#define stm_error(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "user_error"); \
    lua_getfield(L, -5, "__on_validate_error"); \
    lua_getfield(L, -1, field); \
    if (lua_type(L, -3) == LUA_TBOOLEAN && lua_toboolean(L, -3) && lua_toboolean(L, -1)) { \
        luaL_error(L, "%s: %s, \'%s\'\n", STELLAR_ERROR, msg, field); \
    } \
    lua_pop(L, 3);


int stm_new(lua_State *L);
int stm_newindex(lua_State *L);

#endif