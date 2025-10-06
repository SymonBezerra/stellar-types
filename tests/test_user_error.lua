types = require('stellar_types')

types.user_error = true

StringType = types.create_type({
    name = {
        type = 'string',
        validation = function(value)
            return value ~= 'error'
        end
    }
})

pcall(function()
    string = StringType:new({name = 'error'})
end)

assert(string.name == nil)

IntegerType = types.create_type({
    age = {
        type = 'integer',
        validation = function(value)
            return value % 2 == 0
        end
    }
})

pcall(function()
    integer = IntegerType:new({age = 21})
end)

assert(integer.age == nil)

NumberType = types.create_type({
    score = {
        type = 'number',
        validation = function(value)
            return value > 0
        end
    }
})

pcall(function()
    number = NumberType:new({score = -0.5})
end)

assert(number.score == nil)

BooleanType = types.create_type({
    is_active = {
        type = 'boolean',
        validation = function(value)
            return value == true
        end
    }
})

pcall(function()
    boolean = BooleanType:new({is_active = false})
end)

assert(boolean.is_active == nil)

ArrayType = types.create_type({
    tags = {
        type = 'array',
        validation = function(value)
            return #value > 3
        end
    }
})

pcall(function()
    array = ArrayType:new({tags = {1,2}})
end)

assert(array.tags == nil)

DictType = types.create_type({
    config = {
        type = {},
        validation = function(value)
            return value.enabled == true
        end
    }
})

pcall(function()
    dict = DictType:new({config = {enabled = false}})
end)

assert(dict.config == nil)

NestedType = types.create_type({
    username = {
        type = StringType,
        validation = function(value)
            return value.name ~= nil
        end
    },
})

pcall(function()
    nested = NestedType:new({username = string})
end)

assert(nested.username == nil)