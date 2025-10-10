-- execute test_nullable_udata.py with `lupa`
types = require("stellar_types")

ListType = types.create_type('ListType', {
    list = {
        type = types.USERDATA,
        validation = function(value)
            return python.builtins.len(value) > 0
        end
    }
})

obj = ListType:new({ list = list })

assert(obj == nil)

print('All tests passed!')