types = require("stellar_types")

StringType = types.create_type({
    name = {
        ['type'] = types.STRING,
        ['validation'] = function(value)
            return #value > 3
        end
    }
})

str = StringType:new({ name = 'hi' })

IntegerType = types.create_type({
    age = {
        ['type'] = types.INTEGER,
        ['validation'] = function(value)
            return value >= 0
        end
    }
})

assert(str ~= nil)

assert(pcall(function() age = IntegerType:new({ age = -1 }) end) == false)
