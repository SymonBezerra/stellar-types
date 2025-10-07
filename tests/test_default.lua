-- planned feature, not implemented

types = require("stellar_types")

StringType = types.create_type({
    name = {
        type = "string",
        default = 'default',
        validation = function(value)
            return #value > 3
        end
    }
})

print(StringType)
print(StringType.__defaults.name)

str1 = StringType:new({ name = "hi" })
print(str1.name)  -- should print "default"