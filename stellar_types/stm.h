#ifndef STM_H
#define STM_H

#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "types.h"

#define stm_setnil(L) __stm_setnil(L); return 0;

/* Stellar Types module functions */

int stm_new(lua_State *L);
int stm_newindex(lua_State *L);
void __stm_setnil(lua_State *L);

#endif