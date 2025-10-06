-- execute test_error_userdata.py with `lupa`
types = require("stellar_types")

types.error = true

ListType = types.create_type({
    list = {
        type = types.USERDATA,
        validation = function(value)
            return python.builtins.len(value) > 0
        end
    }
})

pcall(function()
    local obj = types.new(ListType, {list = {}})
    local obj2 = types.new(ListType, {list = list})
    local obj3 = types.new(ListType, {list = list2})
end)