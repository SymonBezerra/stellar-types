types = require("stellar_types")

MyType = types.create_type({
    ['name'] = {
        ['type'] = 'string',
        ['validation'] = function(v) return #v > 0 end
    },
    ['value'] = {
        ['type'] = 'any',
        ['validation'] = function(v) return v > 0 end
    },
    ['active'] = {
        ['type'] = 'boolean'
    }
})


instance = MyType:new({
    name = 'Example',
    value = -1,
    active = true
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

nested_instance = NestedType:new({
    description = "A nested instance",
    my_instance = instance
})

print(nested_instance.description) --> A nested instance