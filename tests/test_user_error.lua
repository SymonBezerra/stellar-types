types = require('stellar_types')

types.user_error = true

StringType = types.create_type('StringType', {
    name = {
        type = 'string',
        validation = function(value)
            return value ~= 'error'
        end,
        nullable = true
    }
})

pcall(function()
    string = StringType:new({name = 'error'})
end)

assert(string.name == nil)

IntegerType = types.create_type('IntegerType', {
    age = {
        type = 'integer',
        validation = function(value)
            return value % 2 == 0
        end,
        nullable = true
    }
})

pcall(function()
    integer = IntegerType:new({age = 21})
end)

assert(integer.age == nil)

NumberType = types.create_type('NumberType', {
    score = {
        type = 'number',
        validation = function(value)
            return value > 0
        end,
        nullable = true
    }
})

pcall(function()
    number = NumberType:new({score = -0.5})
end)

assert(number.score == nil)

BooleanType = types.create_type('BooleanType', {
    is_active = {
        type = 'boolean',
        validation = function(value)
            return value == true
        end,
        nullable = true
    }
})

pcall(function()
    boolean = BooleanType:new({is_active = false})
end)

assert(boolean.is_active == nil)

ArrayType = types.create_type('ArrayType', {
    tags = {
        type = 'array',
        validation = function(value)
            return #value > 3
        end,
        nullable = true
    }
})

pcall(function()
    array = ArrayType:new({tags = {1,2}})
end)

assert(array.tags == nil)

DictType = types.create_type('DictType', {
    config = {
        type = {},
        validation = function(value)
            return value.enabled == true
        end,
        nullable = true
    }
})

pcall(function()
    dict = DictType:new({config = {enabled = false}})
end)

assert(dict.config == nil)

NestedType = types.create_type('NestedType', {
    username = {
        type = StringType,
        validation = function(value)
            return value.name ~= nil
        end,
        nullable = true
    },
})

pcall(function()
    nested = NestedType:new({username = string})
end)

assert(nested.username == nil)