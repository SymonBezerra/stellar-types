#ifndef STAUX_H
#define STAUX_H

#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "types.h"

/* Auxiliary functions to be called inside C functions */

int staux_register_type(lua_State *L);
int staux_register_object(lua_State* L);

#endif