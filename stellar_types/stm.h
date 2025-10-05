#ifndef STM_H
#define STM_H

#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "types.h"

#define stm_setnil(L) __stm_setfield(L, FALSE); return 0;
#define stm_setvalue(L) __stm_setfield(L, TRUE); return 0;

/* Stellar Types module functions */

int stm_new(lua_State *L);
int stm_newindex(lua_State *L);
static void __stm_setfield(lua_State *L);

#endif