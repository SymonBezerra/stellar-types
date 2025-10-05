#include "staux.h"

int staux_register_type(lua_State *L) {
    const char* field_name = lua_tostring(L, -1);
    const char* field_type = lua_tostring(L, lua_upvalueindex(1));
    if (lua_type(L, lua_upvalueindex(1)) == LUA_TSTRING) {
        int valid = __staux_validator(L, field_type);
        if (valid < 0) {
            staux_utypeerr(field_type, field_name);
            staux_utypew(field_type, field_name);
        } else if (valid == 0) {
            staux_typeerr(field_type, field_name);
            staux_typew(field_type, field_name);
        }
    } else if (lua_type(L, lua_upvalueindex(1)) == LUA_TTABLE) {
        lua_pushvalue(L, -2);
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pushnil(L);
        int is_array = TRUE;
        while (lua_next(L, -2) != 0) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                is_array = FALSE;
                lua_pop(L, 2); 
                break;
            }
            lua_pop(L, 1); 
        }
        if (!is_array) {
            if (!lua_getmetatable(L, -2)) {
                staux_ctypeerr("Expected specific object (table with metatable) for field", field_name);
                staux_ctypew("Expected specific object (table with metatable) for field", field_name);
            }
            else {
                if (lua_topointer(L, -1) != lua_topointer(L, lua_upvalueindex(1))) {
                    staux_ctypeerr("Wrong type for field", field_name);
                    staux_ctypew("Wrong type for field", field_name);
                } else {
                    staux_confirm();
                }
            }
            lua_pop(L, 1); 
        }
        else {
            int valid = __staux_validator(L, field_type);
            if (valid > 0) {
                staux_confirm();
            } else {
                staux_typeerr(STELLAR_TARRAY, field_name);
                staux_typew(STELLAR_TARRAY, field_name);
            }
        }
        lua_pop(L, 1); 
    }
    return 1;
}

static int __staux_validator(lua_State *L, const char* type_value) {
    if (strcmp(type_value, STELLAR_TSTRING) == 0) {
        return lua_type(L, -2) == LUA_TSTRING;
    } else if (strcmp(type_value, STELLAR_TNUMBER) == 0) {
        return lua_type(L, -2) == LUA_TNUMBER;
    } else if (strcmp(type_value, STELLAR_TBOOLEAN) == 0) {
        return lua_type(L, -2) == LUA_TBOOLEAN;
    } else if (strcmp(type_value, STELLAR_TINTEGER) == 0) {
        return lua_type(L, -2) == LUA_TNUMBER && lua_tointeger(L, -2) == lua_tonumber(L, -2);
    } else if (strcmp(type_value, STELLAR_TFUNCTION) == 0){
        return lua_type(L, -2) == LUA_TFUNCTION;
    } else if (strcmp(type_value, STELLAR_TARRAY) == 0) {
        /* Check if all keys are integers (array-like table) */
        lua_pushnil(L);
        int is_array = TRUE;
        while (lua_next(L, -3)) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                is_array = FALSE;
            }
            if (!is_array) {
                lua_pushboolean(L, FALSE);
                lua_pop(L, 2);
                break;
            }
            lua_pop(L, 1); /* remove value, keep key for next iteration */
        }
        return is_array;
    } else if (strcmp(type_value, STELLAR_TUSERDATA) == 0) {
        return lua_type(L, -2) == LUA_TUSERDATA;
    } else {
        return -1; /* Unknown type */
    }
}