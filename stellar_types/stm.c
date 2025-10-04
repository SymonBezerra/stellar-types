#include "stm.h"

int stm_new(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_getfield(L, 1, "__validators");
    int validators_index = lua_gettop(L);

    lua_newtable(L); /* instance table */
    int instance_index = lua_gettop(L);

    /* Copy keys and values from table at indextrue 1 to instance table */
    lua_pushvalue(L, 1);           /* push MyType */
    lua_setmetatable(L, instance_index); /* set as metatable for instance */

    lua_pushnil(L);  /* first key for lua_next */
    while (lua_next(L, 2) != 0) {
        /* key at -2, value at -1 */
        lua_pushvalue(L, -2); /* copy key */
        lua_pushvalue(L, -2); /* copy value, which moves below key */
        lua_settable(L, instance_index);
        lua_pop(L, 1);
    }
    /* Set the metatable of the instance to the original table (MyType) */
    
    /* Return the instance table */
    lua_pushvalue(L, instance_index);
    return 1;
}

int stm_newindex(lua_State *L) {
    printf("In stm_newindex\n");
    luaL_checktype(L, 1, LUA_TTABLE); /* instance table */
    const char *key = luaL_checkstring(L, 2);

    lua_getmetatable(L, 1);
    /* Get the __validators table from the metatable */
    lua_getfield(L, -1, "__validators");

    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, key);
        if (lua_isfunction(L, -1)) {
            lua_pushvalue(L, 3); /* value to validate */
            lua_pushvalue(L, 2); /* field name */
            lua_call(L, 2, 0);   /* call validator */
        }
        lua_pop(L, 1); /* remove validator or nil */
    }
    lua_pushvalue(L, 2); /* key */
    lua_pushvalue(L, 3); /* value */
    lua_rawset(L, 1);  /* instance[key] = value */

    return 0;
}