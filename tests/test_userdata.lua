-- RUN test_userdata.py INSTEAD

types = require("stellar_types")

UDataType = types.create_type({
    udata = {
        ['type'] = 'userdata',
        ['validation'] = function(value)
            return python.builtins.len(value) > 0
        end
    }
})

udata = UDataType:new({
    udata = list
})
udata2 = UDataType:new({
    udata = list2
})

assert(udata.udata == nil)
assert(udata2.udata ~= nil)