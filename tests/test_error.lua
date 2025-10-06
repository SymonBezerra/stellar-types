types = require("stellar_types")

types.error = true

String = types.create_type({
    name = {
        type = types.STRING,
    }
})

assert(pcall(function() 
    str = String:new({
        name = 1
    })
end) == false)

NumberType = types.create_type({
    value = {
        type = types.NUMBER,
    }
})

assert(pcall(function() 
    num = NumberType:new({
        value = "hello"
    })
end) == false)

IntegerType = types.create_type({
    value = {
        type = types.INTEGER,
    }
})

assert(pcall(function() 
    int = IntegerType:new({
        value = 3.5
    })
end) == false)

BooleanType = types.create_type({
    logic_value = {
        type = types.BOOLEAN,
    }
})

assert(pcall(function() 
    bool = BooleanType:new({
        logic_value = "true"
    })
end) == false)

ArrayType = types.create_type({
    data = {
        type = types.ARRAY,
    }
})

assert(pcall(function() 
    arr = ArrayType:new({
        data = { value = 1 }
    })
end) == false)

DictType = types.create_type({
    dict = {
        type = {}
    }
})

assert(pcall(function() 
    dict = DictType:new({
        dict = "not a table"
    })
end) == false)

FunctionType = types.create_type({
    func = {
        type = types.FUNCTION,
    }
})

assert(pcall(function() 
    func = FunctionType:new({
        func = "not a function"
    })
end) == false)

assert(pcall(function() 
    invalidType = types.create_type({
        field = {
            type = "invalid_type"
        }
    })
end) == false)

assert(pcall(function() 
    invalidType = types.create_type({
        field = {
            not_type = types.STRING
        }
    })
end) == false)

print("All tests passed!")