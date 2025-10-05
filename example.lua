types = require("stellar_types")

-- types.warnings = false

MyType = types.create_type({
    ['name'] = {
        ['type'] = 'string',
        ['validation'] = function(v) return #v > 0 end
    },
    ['value'] = {
        ['type'] = 'number',
        ['validation'] = function(v) return v > 0 end
    },
    ['active'] = {
        ['type'] = 'boolean'
    },
    ['array'] = {
        ['type'] = 'array',
        ['validation'] = function (v)
            for i, n in ipairs(v) do
                if type(n) ~= 'number' then
                    return false
                end
            end
            return true
        end
    }
})


instance = MyType:new({
    name = 'Example',
    value = 0.5,
    active = true,
    array = {1, 2, 3, 4}
})

NestedType = types.create_type({
    ['description'] = {
        ['type'] = 'string'
    },
    ['my_instance'] = {
        ['type'] = MyType
    }
})

print(instance.name) --> Example
print(instance.value) --> 0.5
print(instance.active) --> true
print(instance.array) --> {1, 2, 3, 4}

print(MyType)

false_instance = {
    name = 'Nested Example',
    value = 1.0,
    active = false,
    array = {5, 6, 7, 8}
}

nested_instance = NestedType:new({
    description = "A nested instance",
    my_instance = instance
})

print(nested_instance.description) --> A nested instance