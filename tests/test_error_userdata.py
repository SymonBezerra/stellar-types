import ctypes

import lupa.lua53 as lupa

ctypes.CDLL(lupa.__file__, mode=ctypes.RTLD_GLOBAL)

lua = lupa.LuaRuntime()

lua.globals()['list'] = list()
lua.globals()['list2'] = [1,2,3]

lua.execute('dofile("./test_error_userdata.lua")')