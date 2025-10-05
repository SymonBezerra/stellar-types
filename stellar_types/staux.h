#ifndef STAUX_H
#define STAUX_H

#include <stdio.h>
#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>

#include "types.h"

/* Auxiliary functions to be called inside C functions */

#define staux_typew(type, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "warnings"); \
    if ((lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1)) || lua_type(L, -1) == LUA_TNIL) { \
        fprintf(stderr, "%s: Expected %s for field \'%s\'\n", \
            STELLAR_WARNING, type, field); \
    } \
    lua_pop(L, 2); \
    lua_pushboolean(L, FALSE);

#define staux_typeerr(type, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "error"); \
    if (lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1) || lua_toboolean(L, lua_upvalueindex(2))) { \
        luaL_error(L, "%s: Expected %s for field \'%s\'\n", STELLAR_ERROR, type, field); \
    } \
    lua_pop(L, 1);

#define staux_utypew(type, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "warnings"); \
    if (lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1) || lua_type(L, -1) == LUA_TNIL) { \
        fprintf(stderr, "%s: Unknown type \'%s\' given for field \'%s\'\n", \
            STELLAR_WARNING, type, field); \
    } \
    lua_pop(L, 2); \
    lua_pushboolean(L, FALSE);

#define staux_utypeerr(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "error"); \
    if (lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1) || lua_toboolean(L, lua_upvalueindex(2))) { \
        luaL_error(L, "%s: %s, '%s'\n", STELLAR_ERROR, msg, field); \
    } \
    lua_pop(L, 1);


#define staux_ctypew(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "warnings"); \
    if ((lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1)) || lua_type(L, -1) == LUA_TNIL) { \
        fprintf(stderr, "%s: %s, \'%s\'\n", \
            STELLAR_WARNING, msg, field); \
    } \
    lua_pop(L, 2); \
    lua_pushboolean(L, FALSE);

#define staux_ctypeerr(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "error"); \
    if ((lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1))) { \
        luaL_error(L, "%s: %s, \'%s\'\n", STELLAR_WARNING, msg, field); \
    }

#define staux_confirm() \
    lua_pushboolean(L, TRUE);


int staux_register_type(lua_State *L);
static int __staux_validator(lua_State *L, const char* type_value);

#endif