#include "stellar_types.h"

#ifdef STELLAR_TYPES_LUA
int luaopen_stellar_types(lua_State *L) {
    luaL_Reg functions[] = {
        {"create_type", st_create_type},
        {NULL, NULL}
    };
    luaL_newlib(L, functions);

    lua_pushvalue(L, -1);
    lua_pushcfunction(L, stellar_types_newindex);
    lua_pushstring(L, "__newindex");
    lua_settable(L, -3);

    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, "st");
    return 1;
}
#endif

#ifdef STELLAR_TYPES_PYTHON
int luaopen_stellar_types_python(lua_State *L) {
    luaL_Reg functions[] = {
        {"create_type", st_create_type},
        {NULL, NULL}
    };
    luaL_newlib(L, functions);
    lua_pushvalue(L, -1);
    lua_pushcfunction(L, stellar_types_newindex);
    lua_pushstring(L, "__newindex");
    lua_settable(L, -3);
    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, "st");
    return 1;
}
#endif

int stellar_types_newindex(lua_State *L) {
    if (strcmp(lua_tostring(L, 2), "suppress_warnings") == 0) {
        if (!lua_isboolean(L, 3)) {
            luaL_error(L, "suppress_warnings must be a boolean");
        }
        lua_pushvalue(L, 3);
        lua_pushvalue(L, 2);
        lua_settable(L, 1);
    }
    return 0;
}