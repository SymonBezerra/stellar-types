types = require('stellar_types')

types.user_error = true

StringUType = types.create_type({
    name = {
        type = 'string',
        default = 'default',
        validation = function(value)
            return #value > 3
        end,
        error = true
    }
})

string = StringUType:new({ name = 'hi'})

StringType = types.create_type({
    name = {
        type = 'string',
        default = 'default',
    }
})

string2 = StringType:new({})

assert(string.name == 'default')
assert(string2.name == 'default')

IntegerUType = types.create_type({
    age = {
        type = 'integer',
        default = 25,
        validation = function(value)
            return value >= 0
        end
    }
})

integer = IntegerUType:new({ age = -5 })

IntegerType = types.create_type({
    age = {
        type = 'integer',
        default = 25,
    }
})

integer2 = IntegerType:new({})

print(integer.age)
assert(integer2.age == 25)

print('Default value test passed')