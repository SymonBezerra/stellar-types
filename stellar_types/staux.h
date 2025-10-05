#ifndef STAUX_H
#define STAUX_H

#include <string.h>

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "types.h"

#define staux_error(msg) fprintf(stderr, "%s: %s\n", STELLAR_WARNING, msg); lua_pushboolean(L, FALSE);
#define staux_confirm() lua_pushboolean(L, TRUE);

/* Auxiliary functions to be called inside C functions */

int staux_register_type(lua_State *L);
int staux_register_object(lua_State* L);

#endif