#ifndef ST_H
#define ST_H

#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

#include "stm.h"
#include "staux.h"

/* Lua module function definitions */

int st_create_type(lua_State *L);

#endif