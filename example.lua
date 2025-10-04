types = require("stellar_types")

MyType = types.create_type({
    ['name'] = {
        ['type'] = 'string',
        ['validation'] = function(v) return #v > 0 end
    },
    ['value'] = {
        ['type'] = 'float',
        ['validation'] = function(v) return v >= 0 end
    },
    ['active'] = {
        ['type'] = 'boolean'
    },
    -- ['complex'] = {
    --     ['type'] = 'object',
    --     ['schema'] = {
    --         ['obj_name'] = {
    --             ['type'] = 'string'
    --         },
    --         ['obj_value'] = {
    --             ['type'] = 'string'
    --         }
    --     }
    -- },
})

instance = MyType:new({
    name = "Example",
    value = 0.5,
    active = true
})

print(instance.name) --> Example
print(instance.value) --> 0.5
print(instance.active) --> true


-- TODO: add validation for reattribution of values

complex_schema = {
    ['type'] = {
        ['type'] = MyType
    }
}

NewType = types.create_type({
    ['description'] = {
        ['type'] = 'string'
    },
    ['count'] = {
        ['type'] = 'integer',
        ['validation'] = function(v) return v >= 0 end
    }
})

new_instance = NewType:new({
    description = "A new type instance",
    count = 10
})

ComplexType = types.create_type(complex_schema)


complex_instance = ComplexType:new({
    type = new_instance
})

print(complex_instance.type.name) --> Example