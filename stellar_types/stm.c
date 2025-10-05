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
    const char *key = luaL_checkstring(L, 2);

    lua_getmetatable(L, 1);
    /* Get the __validators table from the metatable */
    lua_getfield(L, -1, "__validators");

    lua_getfield(L, -1, key);
    if (lua_isfunction(L, -1)) {
        lua_pushvalue(L, 3); /* value to validate */
        lua_pushvalue(L, 2); /* field name */
        lua_call(L, 2, 1);   /* call validator */
        if (!lua_toboolean(L, -1)) {
            return 0; /* validation failed, error already reported */
        }
    }
    lua_pop(L, 2); /* remove validator and its result */
    lua_pushvalue(L, -1);

    lua_getfield(L, -1, "__extra_validators");
    lua_getfield(L, -1, key);
        if (!lua_isnil(L, -1)) {
        lua_pushvalue(L, 3);
        lua_call(L, 1, 1);
        if (!lua_isboolean(L, -1)) {
            stm_error("User-defined validation did not return a boolean for field", key);
            stm_warning("User-defined validation did not return a boolean for field", key);
        } else if (!lua_toboolean(L, -1)) {
            stm_error("User-defined validation failed for field", key);
            stm_warning("User-defined validation failed for field", key);
        }
    }
    lua_pop(L, 2); /* remove __extra_validators and its field value (or nil) */
    __stm_setfield(L);
    return 0;
}

static void __stm_setfield(lua_State *L) {
    lua_pushvalue(L, 2); /* key */
    lua_pushvalue(L, 3); /* value */
    lua_rawset(L, 1);  /* instance[key] = nil */
}