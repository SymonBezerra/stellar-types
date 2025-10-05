types = require("stellar_types")

-- types.warnings = false --> disable warnings

StrType = types.create_type({
    name = {
        ['type'] = 'string',
        ['validation'] = function(value)
            return #value > 3
        end
    }
})

str = StrType:new({
    name = "hello"
})

str2 = StrType:new({
    name = "hi"
})

assert(str.name ~= nil)
assert(str2.name == nil)

NumberType = types.create_type({
    value = {
        ['type'] = 'number',
        ['validation'] = function(value)
            return value >= 0
        end
    }
})

number = NumberType:new({
    value = 25
})
number2 = NumberType:new({
    value = 0.5
})
number3 = NumberType:new({
    value = -5
})

assert(number.value == 25)
assert(number2.value == 0.5)
assert(number3.value == nil)

IntegerType = types.create_type({
    value = {
        ['type'] = 'integer',
        ['validation'] = function(value)
            return value % 2 == 0
        end
    }
})

integer = IntegerType:new({
    value = 10
})
integer2 = IntegerType:new({
    value = 5
})
integer3 = IntegerType:new({
    value = 2.5
})

assert(integer.value == 10)
assert(integer2.value == nil)
assert(integer3.value == nil)

BooleanType = types.create_type({
    logic_value = {
        ['type'] = 'boolean',
    }
})

boolean = BooleanType:new({
    logic_value = true
})
boolean2 = BooleanType:new({
    logic_value = false
})

assert(boolean.logic_value == true)
assert(boolean2.logic_value == false)

ArrayType = types.create_type({
    data = {
        ['type'] = 'array',
        ['validation'] = function(value)
            if #value == 0 then
                return false
            end
            valid = true
            for _, v in ipairs(value) do
                if type(v) ~= 'number' then
                    valid = false
                    break
                end
            end
            return valid
        end
    }
})

array = ArrayType:new({
    data = {1, 2, 3}
})
array2 = ArrayType:new({
    data = {'1'}
})
array3 = ArrayType:new({
    data = {
        indexed = '1'
    }
})

assert(array.data ~= nil)
assert(array2.data == nil)
assert(array3.data == nil)

PrimitiveType = types.create_type({
    attr = {
        type = 'string',
        validation = function(value)
            return #value > 0
        end
    }
})

primitive = PrimitiveType:new({
    attr = "value"
})

primitive2 = PrimitiveType:new({
    attr = "toomanycharacters"
})

NestedType = types.create_type({
    nested = {
        type = PrimitiveType,
        validation = function(value)
            return #value.attr < 10
        end
    }
})

nested = NestedType:new({
    nested = primitive
})

nested2 = NestedType:new({
    nested = primitive2
})

DictType = types.create_type({
    obj = {
        type = {},
        validation = function(value)
            return value['key'] ~= nil and type(value['key']) == 'number' and value['key'] > 0
        end
    }
})

dict = DictType:new({
    obj = {key = 5}
})

-- dict2 = DictType:new({
--     dict = {key = -1}
-- })

-- dict3 = DictType:new({
--     dict = {key = 'value'}
-- })
-- dict4 = DictType:new({
--     dict = {another_key = 10}
-- })

-- assert(dict.dict ~= nil)
-- assert(dict2.dict == nil)
-- assert(dict3.dict == nil)
-- assert(dict4.dict == nil)

assert(nested.nested ~= nil)
assert(nested2.nested == nil)

FunctionType = types.create_type({
    func = {
        type = 'function',
        validation = function(value)
            return debug.getinfo(value).nparams == 2
        end
    }
})

func = FunctionType:new({
    func = function(a, b) return a + b end
})

func2 = FunctionType:new({
    func = function(a) return a end
})

assert(func.func ~= nil)
assert(func2.func == nil)

print("All tests passed!")