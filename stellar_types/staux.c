#include "staux.h"

int staux_register_type(lua_State *L) {
    if (lua_type(L, lua_upvalueindex(1)) == LUA_TSTRING) {
        const char* type_value = lua_tostring(L, lua_upvalueindex(1));
        const char* field_name = lua_tostring(L, -1);
        if (strcmp(type_value, STELLAR_TSTRING) == 0) {
            if (lua_type(L, -2) != LUA_TSTRING) {
                staux_error("Expected a string for field");
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TNUMBER) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER) {
                staux_error("Expected a number for field");
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TBOOLEAN) == 0) {
            if (lua_type(L, -2) != LUA_TBOOLEAN) {
                staux_error("Expected a boolean for field");
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TINTEGER) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                staux_error("Expected an integer for field");
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TFLOAT) == 0) {
            if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) == lua_tonumber(L, -2)) {
                staux_error("Expected a float (decimal) for field");
            } else {
                staux_confirm();
            }
        } else if (strcmp(type_value, STELLAR_TARRAY) == 0) {
            if (lua_type(L, -2) != LUA_TTABLE) {
                staux_error("Expected an array (table) for field");
            }
            /* Check if all keys are integers (array-like table) */
            lua_pushnil(L);
            int is_array = TRUE;
            while (lua_next(L, -4)) {
                if (lua_type(L, -2) != LUA_TNUMBER || lua_tointeger(L, -2) != lua_tonumber(L, -2)) {
                    is_array = FALSE;
                    fprintf(stderr, "Expected array (table with integer keys) for field '%s'", field_name);
                }
                lua_pop(L, 1); /* remove value, keep key for next iteration */
                if (!is_array) {
                    lua_pushboolean(L, FALSE);
                    break;
                }
            }
            if (is_array) {
                staux_confirm();
            }
        } else {
            fprintf(stderr, "Unsupported type \'%s\' for field in type \'%s\'", type_value, field_name);
        }
    } else if (lua_type(L, lua_upvalueindex(1)) == LUA_TTABLE) {
        if (lua_getmetatable(L, -2) == 0) {
            staux_error("Expected an object (table with metatable) for field");
        }
        else if (!lua_rawequal(L, -1, lua_upvalueindex(1))) {
            staux_error("Wrong type for field");
        } else {
            staux_confirm();
        }
        lua_pop(L, 1);
    }
    return 1;
}