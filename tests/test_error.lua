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
        String({ name = v })
        NumberType({ value = v })
        IntegerType({ value = v })
        BooleanType({ logic_value = v })
        ArrayType({ data = v })
        DictType({ dict = v })
        FunctionType({ func = v })
    end)
end

print("All tests passed!")