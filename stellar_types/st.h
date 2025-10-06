#ifndef ST_H
#define ST_H

#include "stm.h"
#include "staux.h"

/* Lua module function definitions */

#define st_tcheck(type) ( \
    strcmp(type, STELLAR_TANY) == 0 || \
    strcmp(type, STELLAR_TSTRING) == 0 || \
    strcmp(type, STELLAR_TNUMBER) == 0 || \
    strcmp(type, STELLAR_TINTEGER) == 0 || \
    strcmp(type, STELLAR_TBOOLEAN) == 0 || \
    strcmp(type, STELLAR_TARRAY) == 0 || \
    strcmp(type, STELLAR_TFUNCTION) == 0 || \
    strcmp(type, STELLAR_TUSERDATA) == 0 )

#define st_utypeerr(field, type) \
    luaL_error(L, "%s: Unknown type \'%s\' given for field \'%s\'\n", STELLAR_ERROR, type, field);

#define st_itypeerr(field, type) \
    luaL_error(L, "Type specification missing or invalid for field '%s': %s", field, type);

int st_create_type(lua_State *L);

#endif