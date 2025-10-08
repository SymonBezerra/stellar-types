types = require('stellar_types')

StringUType = types.create_type('StringUType', {
    name = {
        type = 'string',
        validation = function(value)
            return #value > 3
        end,
        default = 'default'
    }
})

string = StringUType:new({})

StringType = types.create_type('StringType', {
    name = {
        type = 'string',
        default = 'default',
    }
})

string2 = StringType:new({})

assert(string.name == 'default')
assert(string2.name == 'default')

IntegerUType = types.create_type('IntegerUType', {
    age = {
        type = 'integer',
        default = 18,
        validation = function(value)
            return value >= 0
        end
    }
})

integer = IntegerUType:new({ age = -5 })

IntegerType = types.create_type('IntegerType', {
    age = {
        type = 'integer',
        default = 25,
    }
})

integer2 = IntegerType:new({})

assert(integer.age == 18)
assert(integer2.age == 25)

print('Default value test passed')