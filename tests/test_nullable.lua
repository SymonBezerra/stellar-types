types = require("stellar_types")

StringType = types.create_type('StringType', {
    name = {
        ['type'] = types.STRING,
        ['validation'] = function(value)
            return #value > 3
        end,
        ['nullable'] = false
    }
})

str = StringType:new({ name = 'hi' })

IntegerType = types.create_type('IntegerType', {
    age = {
        ['type'] = types.INTEGER,
        ['validation'] = function(value)
            return value >= 0
        end
    }
})

assert(pcall(function() age = IntegerType:new({ age = -1 }) end) == true)

DictType = types.create_type('DictType', {
    data = {
        ['type'] = {},
        ['validation'] = function(value)
            return value.attr ~= nil
        end
    }
})

dict = DictType:new({ data = { attr = 'value' } })

print('All tests passed!')