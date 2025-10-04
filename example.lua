types = require("stellar_types")

MyType = types.create_type('MyType', {
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

print(instance.name)