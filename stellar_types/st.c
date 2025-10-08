#include "st.h"

int st_create_type(lua_State *L) {

    lua_newtable(L);
    int class_index = lua_gettop(L);

    lua_pushcfunction(L, stm_new);
    lua_setfield(L, class_index, "new");

    lua_newtable(L);
    int validators_index = lua_gettop(L);

    lua_newtable(L);
    int defaults_index = lua_gettop(L);

    lua_newtable(L);
    int nullable_index = lua_gettop(L);

    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        if (!lua_istable(L, -1)) {
            luaL_error(L, "Expected a table for field '%s', got '%s'", lua_tostring(L, -2), luaL_typename(L, -1));
        }
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

        lua_getfield(L, -1, STELLAR_DEFAULT_OPTION);
        if (!lua_isnil(L, -1)) {
            lua_pushvalue(L, -1);
            lua_getfield(L, validators_index, name);
            lua_pushvalue(L, -2);
            lua_pushstring(L, name);
            lua_call(L, 2, 1);
            if (!lua_toboolean(L, -1)) {
                st_defaulterr(name);
            }
            lua_pop(L, 1);
            lua_setfield(L, defaults_index, name);
        }
        lua_pop(L, 1);
        
        lua_getfield(L, -1, STELLAR_NULLABLE_OPTION);
        if (lua_toboolean(L, -1)) {
            lua_pushvalue(L, -1);
            lua_setfield(L, nullable_index, name);
        } else {
            lua_pushboolean(L, FALSE);
            lua_setfield(L, nullable_index, name);
        }
        lua_pop(L, 2);
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
            lua_getfield(L, defaults_index, name);
            if (!lua_isnil(L, -1)) {
                lua_call(L, 1, 1);
                if (!lua_toboolean(L, -1) || !lua_isboolean(L, -1)) {
                    st_udefaulterr(name);
                }
            } else {
                lua_pop(L, 1);
            }
        } else if (!lua_isnil(L, -1)) {
            st_validationerr(name);
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
    lua_pushvalue(L, class_index);
    lua_setfield(L, -2, STELLAR_INDEX);

    lua_pushvalue(L, validators_index);
    lua_setfield(L, class_index, STELLAR_VALIDATORS);
    lua_pushcfunction(L, stm_newindex);
    lua_setfield(L, class_index, STELLAR_NEWINDEX);
    lua_pushvalue(L, extra_validators_index);
    lua_setfield(L, class_index, STELLAR_EXTRA_VALIDATORS);
    lua_pushvalue(L, error_index);
    lua_setfield(L, class_index, STELLAR_ON_VALIDATE_ERROR);
    lua_pushvalue(L, defaults_index);
    lua_setfield(L, class_index, STELLAR_DEFAULTS);
    lua_pushstring(L, STELLAR_TYPES_MODULE);
    lua_setfield(L, class_index, STELLAR_CLASS);
    lua_pushvalue(L, nullable_index);
    lua_setfield(L, class_index, STELLAR_ISNULLABLE);
    lua_pushvalue(L, class_index);

    return 1;
}