import ctypes

import lupa.lua53 as lupa

ctypes.CDLL(lupa.__file__, mode=ctypes.RTLD_GLOBAL)

lua = lupa.LuaRuntime()

lua.globals()['list'] = list()

lua.execute('dofile("./test_nullable_udata.lua")')