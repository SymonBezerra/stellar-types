#ifndef STM_H
#define STM_H

#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

/* Stellar Types module functions */

int stm_new(lua_State *L);
int stm_newindex(lua_State *L);

#endif