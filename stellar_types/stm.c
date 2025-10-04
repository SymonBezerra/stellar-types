#include "stm.h"

int stm_new(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_getfield(L, 1, "__validators");
    int validators_index = lua_gettop(L);

    lua_newtable(L); /* instance table */
    int instance_index = lua_gettop(L);

    /* Copy keys and values from table at index 1 to instance table */

    lua_pushnil(L);  /* first key for lua_next */
    while (lua_next(L, 2) != 0) {
        /* key at -2, value at -1 */
        lua_pushvalue(L, -2); /* copy key */
        lua_pushvalue(L, -1); /* copy value */
        lua_settable(L, instance_index);

        lua_getfield(L, validators_index, lua_tostring(L, -2));
        lua_pushvalue(L, -3); /* push value to validate */
        lua_call(L, 1, 0);    /* call validator */
        lua_pop(L, 1); /* remove value, keep key for next iteration */
    }

    return 1;
}
