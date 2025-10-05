import lupa.lua53 as lupa

lua = lupa.LuaRuntime()

lua.globals()['complex'] = list()

lua.execute('dofile("./userdata_example.lua")')