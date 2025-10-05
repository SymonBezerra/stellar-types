#include "st.h"

int st_create_type(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE); /* check the schema passed to the constructor */

    lua_newtable(L); /* class table */
    int class_index = lua_gettop(L);

    /* methods table */
    lua_newtable(L);
    int methods_index = lua_gettop(L);

    lua_pushcfunction(L, stm_new);
    lua_setfield(L, methods_index, "new");

    lua_newtable(L);
    int validators_index = lua_gettop(L);

    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        const char* name = lua_tostring(L, -2);
        lua_getfield(L, -1, STELLAR_TYPE_OPTION);
        if (lua_type(L, -1) == LUA_TSTRING) {
            const char* type_value = lua_tostring(L, -1);
            lua_pushstring(L, type_value);
        } else if (lua_type(L, -1) == LUA_TTABLE) {
            lua_pushvalue(L, -1); /* push the metatable */
        } else {
            luaL_error(L, "Type specification missing or invalid for field \'%s\': %s", name, lua_typename(L, lua_type(L, -1)));
        }
        
        lua_pop(L, 1);
        lua_pushcclosure(L, staux_register_type, 1);

        lua_setfield(L, validators_index, name);

        lua_pop(L, 1);
    }

    lua_newtable(L); /* __extra_validators table */
    int extra_validators_index = lua_gettop(L);

    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        const char* name = lua_tostring(L, -2);
        lua_getfield(L, -1, STELLAR_VALIDATION_OPTION);
        if (lua_isfunction(L, -1)) {
            lua_pushvalue(L, -1);
            lua_setfield(L, extra_validators_index, name);
        } else if (!lua_isnil(L, -1)) {
            luaL_error(L, "Validation for field \'%s\' is not a function", name);
        }
        lua_pop(L, 2);
    }

    /* set methods table as metatable for class table */
    lua_newtable(L); /* metatable for class */
    lua_pushvalue(L, methods_index);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, class_index);
    /* set schema as __validators field in class table */
    lua_pushvalue(L, validators_index);
    lua_setfield(L, class_index, "__validators");
    lua_pushcfunction(L, stm_newindex);
    lua_setfield(L, class_index, "__newindex");
    lua_pushvalue(L, extra_validators_index);
    lua_setfield(L, class_index, "__extra_validators");
    lua_pushvalue(L, class_index);

    return 1;
}