#include "stellar_types.h"

int luaopen_stellar_types(lua_State *L) {
    luaL_Reg functions[] = {
        {"create_type", st_create_type},
        {NULL, NULL}
    };
    luaL_newlib(L, functions);
    return 1;
}