types = require("stellar_types")

StringType = types.create_type('StringType', {
    name = {
        ['type'] = types.STRING,
        ['validation'] = function(value)
            return #value > 3
        end
    }
})

str = StringType:new({ name = 'hi' })

assert(str == nil)

IntegerType = types.create_type('IntegerType', {
    age = {
        ['type'] = types.INTEGER,
        ['validation'] = function(value)
            return value >= 0
        end
    }
})

int = IntegerType:new({ age = -5 })

assert(int == nil)


DictType = types.create_type('DictType', {
    data = {
        ['type'] = {},
        ['validation'] = function(value)
            return value.attr ~= nil
        end
    }
})

dict = DictType:new({ data = {} })

assert(dict == nil)

BooleanType = types.create_type('BooleanType', {
    flag = {
        ['type'] = types.BOOLEAN,
        ['nullable'] = false
    }
})

bool = BooleanType:new({ flag = nil })

assert(bool == nil)

ArrayType = types.create_type('ArrayType', {
    items = {
        ['type'] = { types.INTEGER },
        ['validation'] = function(value)
            return #value > 3
        end
    }
})

array = ArrayType:new({ items = {1, 2} })

assert(array == nil)

NumberType = types.create_type('NumberType', {
    score = {
        ['type'] = types.NUMBER,
        ['validation'] = function(value)
            return value >= 0
        end
    }
})

number = NumberType:new({ score = -10 })

assert(number == nil)

AnyType = types.create_type('AnyType', {
    anything = {
        ['type'] = types.ANY,
        ['validation'] = function(value)
            return type(value) == 'string' or type(value) == 'number'
        end
    }
})

any = AnyType:new({ anything = true })

assert(any == nil)

SimpleType = types.create_type('SimpleType', {
    simple = {
        ['type'] = types.ARRAY,
        ['validation'] = function(value)
            return #value > 0
        end
    }
})

NestedType = types.create_type('NestedType', {
    attr = {
        ['type'] = SimpleType,
        ['validation'] = function(value)
            return value.simple[1] == 1
        end
    }
})

nested = NestedType:new({ attr = { simple = {} } })

assert(nested == nil)

FunctionType = types.create_type('FunctionType', {
    func = {
        ['type'] = types.FUNCTION
    }
})

func = FunctionType:new({ func = 123 })

assert(func == nil)

print('All tests passed!')