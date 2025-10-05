import ctypes

import lupa.lua53 as lupa

ctypes.CDLL(lupa.__file__, mode=ctypes.RTLD_GLOBAL)

lua = lupa.LuaRuntime()

lua.globals()['complex'] = list()

lua.execute('package.cpath = "./examples/?.so;" .. package.cpath')

lua.execute('dofile("./userdata_example.lua")')