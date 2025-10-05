#include "staux.h"

int staux_register_type(lua_State *L) {
    const char* field_name = lua_tostring(L, -1);
    if (lua_type(L, lua_upvalueindex(1)) == LUA_TSTRING) {
        const char* type_value = lua_tostring(L, lua_upvalueindex(1));
        if (strcmp(type_value, STELLAR_TSTRING) == 0) {
            if (lua_type(L, -2) != LUA_TSTRING) {
                staux_fielderror("Expected a string for field", field_name);
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TNUMBER) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER) {
                staux_fielderror("Expected a number for field", field_name);
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TBOOLEAN) == 0) {
            if (lua_type(L, -2) != LUA_TBOOLEAN) {
                staux_fielderror("Expected a boolean for field", field_name);
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TINTEGER) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                staux_fielderror("Expected an integer for field", field_name);
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TFLOAT) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) == lua_tonumber(L, -2)) {
                staux_fielderror("Expected a float (decimal) for field", field_name);
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TARRAY) == 0) {
            if (lua_type(L, -2) != LUA_TTABLE) {
                staux_fielderror("Expected an array (table) for field", field_name);
            }
            /* Check if all keys are integers (array-like table) */
            lua_pushnil(L);
            int is_array = TRUE;
            while (lua_next(L, -3)) {
                if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                    is_array = FALSE;
                    fprintf(stderr, "Expected array (table with integer keys) for field '%s'", field_name);
                }
                if (!is_array) {
                    lua_pushboolean(L, FALSE);
                    lua_pop(L, 2);
                    break;
                }
                lua_pop(L, 1); /* remove value, keep key for next iteration */
            }
            if (is_array) {
                staux_confirm();
            }
        } else {
            fprintf(stderr, "Unsupported type \'%s\' for field in type \'%s\'", type_value, field_name);
        }
    } else if (lua_type(L, lua_upvalueindex(1)) == LUA_TTABLE) {
        if (lua_getmetatable(L, -2) == 0) {
            staux_fielderror("Expected an object (table with metatable) for field", field_name);
        }
        else if (!lua_rawequal(L, -1, lua_upvalueindex(1))) {
            staux_fielderror("Wrong type for field", field_name);
        } else {
            staux_confirm();
        }
        lua_pop(L, 1);
    }
    return 1;
}