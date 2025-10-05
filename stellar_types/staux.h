#ifndef STAUX_H
#define STAUX_H

#include <stdio.h>
#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "types.h"

#define staux_fielderror(msg, field) \
    lua_getfield(L, LUA_REGISTRYINDEX, "st"); \
    lua_getfield(L, -1, "warnings"); \
    if ((lua_type(L, -1) == LUA_TBOOLEAN && lua_toboolean(L, -1)) || lua_type(L, -1) == LUA_TNIL) { \
        fprintf(stderr, "%s: %s, '%s'\n", \
            STELLAR_WARNING, msg, field); \
    } \
    lua_pop(L, 2); \
    lua_pushboolean(L, FALSE);

#define staux_confirm() \
    lua_pushboolean(L, TRUE);

/* Auxiliary functions to be called inside C functions */

int staux_register_type(lua_State *L);

#endif