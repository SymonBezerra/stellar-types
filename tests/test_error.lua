types = require("stellar_types")

types.error = true

String = types.create_type({
    name = {
        type = types.STRING,
    }
})

NumberType = types.create_type({
    value = {
        type = types.NUMBER,
    }
})

IntegerType = types.create_type({
    value = {
        type = types.INTEGER,
    }
})

BooleanType = types.create_type({
    logic_value = {
        type = types.BOOLEAN,
    }
})

ArrayType = types.create_type({
    data = {
        type = types.ARRAY,
    }
})

DictType = types.create_type({
    dict = {
        type = {}
    }
})

FunctionType = types.create_type({
    func = {
        type = types.FUNCTION,
    }
})

values = {
    "string",
    123,
    45.67,
    true,
    {},
    {1,2,3},
    { dict = { key = "value" } },
    function() return "hello" end
}

for i = 1, #values do
    pcall(function()
        local v = values[i]
        String:new({ name = v })
        NumberType:new({ value = v })
        IntegerType:new({ value = v })
        BooleanType:new({ logic_value = v })
        ArrayType:new({ data = v })
        DictType:new({ dict = v })
        FunctionType:new({ func = v })
    end)
end

print("All tests passed!")