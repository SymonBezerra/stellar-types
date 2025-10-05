-- this script must be called from Python's `lupa` module
-- it demonstrates how to use Stellar with Python userdata types
types = require("stellar_types")

UserdataTypes = types.create_type({
    ['list'] = {
        ['type'] = 'userdata',
        ['validation'] = function(v)
            return python.builtins.str(python.builtins.type(v)) == '<class \'list\'>'
        end
    } 
})

instance = UserdataTypes:new({
    list = complex
})

print(instance.list)