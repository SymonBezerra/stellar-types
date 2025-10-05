# StellarTypes - A Pydantic inspired library for Lua tables

**WORK IN PROGRESS**

`StellarTypes` is a simple validation module for Lua tables inspired by Python's Pydantic. It creates object-oriented tables (based on Ierusalimschy's Programming in Lua approach for OOP using the data structure) with an enforced schema, so types are validated on instance creation. Let's see an example:

```lua
types = require("stellar_types")

Config = types.create_type({
    ['value'] = {
        ['type'] = 'string'
    }
})

instance = Config:new({
    value = 'config value'
})

instance2 = Config:new({
    value = 0
})

print(instance.value) --> 'config value'
print(instance2.value) --> nil
```

As a default behavior, invalid instances return `nil` values to the fields, outputing a warning to `stderr`. This behavior can be altered if desired by the user:

```lua
types = require("stellar_types")

types.warnings = false -- suppress stderr warnings
types.errors = true -- exception raising on validation failure
types.user_error = true -- exception raising on user-defined validation failure
```

Each table attribute is a string-indexed table with a few fields:

1. `type`, where possible values are:
    + `string`
    + `number` (float)
    + `integer`
    + `boolean`
    + `array` (integer-indexed table)
    + `object` (string-indexed table)
    + `function`
    + `userdata`
    + `any`
2. `validation`, a validation function that returns a boolean value
3. `error`, a boolean value that triggers an exception if the `validation` callback returns a `false` value (must have `require('stellar_types').user_error = true` enabled)

```lua
Config = types.create_type({
    ['value'] = {
        ['type'] = 'string',
        ['validation'] = function(v) return #v > 0 end,
        ['error'] = true
    }
})
```

## Integration with Python

The `stellar_types_python` module is intended to be used with the `lupa` Python library in the following way:

```python
import ctypes

import lupa.lua53 as lupa

ctypes.CDLL(lupa.__file__, mode=ctypes.RTLD_GLOBAL) # in order lupa.LuaRuntime shared objects as Lua headers

lua = lupa.LuaRuntime()
```

## Validating array-like tables

You can define the subtype of the array table using the user-defined validation:

```lua
ArrayType = types.create_type({
    ['arr'] = {
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
```

## Validating object-like tables

Object-like tables are validated via their metatable (inheritance), though other validations can be user-defined.

## Composite types

You may define a composite type using the user-defined validation:

```lua
CompositeType = types.create_type({
    ['attr'] = {
        ['type'] = 'any',
        ['validation'] = function(v)
            return type(v) == 'string' or type(v) == 'number'
        end
    }
})
```

## Function values

Function values cannot be limited on what functionalities they may perform, i.e. if they will be used as a procedure or a method-like function. Proceed with caution!

## Userdata values

While there is a way to validate Lua-defined userdata, there is no way to validate their static C types dynamically. However, the user-defined validation can work around this limitation of the interpreter:

```lua
types = require("stellar_types_python") -- example with lupa

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

print(instance.list) --> []
```