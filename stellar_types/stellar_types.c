#include "stellar_types.h"

int luaopen_stellar_types(lua_State *L) {
    luaL_Reg functions[] = {
        {"create_type", st_create_type},
        {NULL, NULL}
    };
    luaL_newlib(L, functions);

    lua_pushvalue(L, -1);

    lua_pushstring(L, STELLAR_TANY);
    lua_setfield(L, -2, "ANY");
    lua_pushstring(L, STELLAR_TSTRING);
    lua_setfield(L, -2, "STRING");
    lua_pushstring(L, STELLAR_TNUMBER);
    lua_setfield(L, -2, "NUMBER");
    lua_pushstring(L, STELLAR_TBOOLEAN);
    lua_setfield(L, -2, "BOOLEAN");
    lua_pushstring(L, STELLAR_TINTEGER);
    lua_setfield(L, -2, "INTEGER");
    lua_pushstring(L, STELLAR_TARRAY);
    lua_setfield(L, -2, "ARRAY");
    lua_pushstring(L, STELLAR_TFUNCTION);
    lua_setfield(L, -2, "FUNCTION");
    lua_pushstring(L, STELLAR_TUSERDATA);
    lua_setfield(L, -2, "USERDATA");

    lua_newtable(L);
    lua_setmetatable(L, -2);

    lua_getmetatable(L, -1);
    lua_pushcfunction(L, stellar_types_newindex);
    lua_setfield(L, -2, STELLAR_NEWINDEX);

    lua_pop(L, 1);

    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, "st");
    return 1;
}

int stellar_types_newindex(lua_State *L) {
    if (strcmp(lua_tostring(L, 2), "warnings") == 0 ||
        strcmp(lua_tostring(L, 2), "error") == 0 ||
        strcmp(lua_tostring(L, 2), "user_error") == 0
    ) {
        if (!lua_isboolean(L, 3)) {
            luaL_error(L, "%s option must be a boolean", lua_tostring(L, 2));
        }
        lua_pushvalue(L, 2);
        lua_pushvalue(L, 3);
        lua_rawset(L, 1);
    } else {
        luaL_error(L, "Unknown option '%s'", lua_tostring(L, 2));
    }
    return 0;
}