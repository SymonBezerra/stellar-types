#ifndef STELLAR_TYPES_H
#define STELLAR_TYPES_H

#include "st.h"

#ifdef STELLAR_TYPES_LUA
int luaopen_stellar_types(lua_State *L);
#endif
#ifdef STELLAR_TYPES_PYTHON
int luaopen_stellar_types_python(lua_State *L);
#endif
int stellar_types_newindex(lua_State *L);

#endif