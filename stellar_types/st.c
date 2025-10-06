#include "st.h"

int st_create_type(lua_State *L) {
    lua_newtable(L);
    int class_index = lua_gettop(L);

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
            if (!st_tcheck(lua_tostring(L, -1))) {
                st_utypeerr(name, lua_tostring(L, -1));
            }
            const char* type_value = lua_tostring(L, -1);
            if (strcmp(type_value, STELLAR_TANY) == 0) {
                lua_pop(L, 2);
                continue;
            }
            lua_pushstring(L, type_value);
        } else if (lua_type(L, -1) == LUA_TTABLE) {
            lua_pushvalue(L, -1);
        } else {
            st_itypeerr(name, lua_typename(L, lua_type(L, -1)));
        }
        lua_pop(L, 1);
        lua_getfield(L, -2, STELLAR_ERROR_OPTION);
        lua_pushcclosure(L, staux_register_type, 2);
        lua_setfield(L, validators_index, name);

        lua_pop(L, 1);
    }

    lua_newtable(L);
    int extra_validators_index = lua_gettop(L);

    lua_newtable(L);
    int error_index = lua_gettop(L);

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
        lua_pop(L, 1);

        lua_getfield(L, -1, STELLAR_ERROR_OPTION);
        if (lua_toboolean(L, -1)) {
            lua_pushvalue(L, -1);
            lua_setfield(L, error_index, name);
        }
        lua_pop(L, 2);
    }

    lua_newtable(L);
    lua_pushvalue(L, methods_index);
    lua_setfield(L, -2, STELLAR_INDEX);
    lua_setmetatable(L, class_index);

    lua_pushvalue(L, validators_index);
    lua_setfield(L, class_index, STELLAR_VALIDATORS);
    lua_pushcfunction(L, stm_newindex);
    lua_setfield(L, class_index, STELLAR_NEWINDEX);
    lua_pushvalue(L, extra_validators_index);
    lua_setfield(L, class_index, STELLAR_EXTRA_VALIDATORS);
    lua_pushvalue(L, error_index);
    lua_setfield(L, class_index, STELLAR_ON_VALIDATE_ERROR);
    lua_pushvalue(L, class_index);

    return 1;
}