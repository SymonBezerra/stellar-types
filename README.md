# StellarTypes - A Pydantic inspired library for Lua tables

`StellarTypes` is a simple validation module for Lua tables inspired by Python's Pydantic. It creates object-oriented tables (based on Ierusalimschy's Programming in Lua approach for OOP using the data structure) with an enforced schema, so types are validated on instance creation. Let's see an example:

```lua
types = require("stellar_types")

Config = types.create_type('Config', {
    ['value'] = {
        ['type'] = types.STRING
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

The first argument is a class name that will be passed to a `__name` attribute and also used in the `__tostring` metamethod. The second argument is a table that will receive the schema for the object we are creating.

As a default behavior, invalid instances return `nil` values to the fields, outputing a warning to `stderr`. This behavior can be altered if desired by the user:

```lua
types = require("stellar_types")

types.warnings = false -- suppress stderr warnings
types.errors = true -- exception raising on validation failure
types.user_error = true -- exception raising on user-defined validation failure
```

> Every error on `create_type` raises an exception, while errors on instance creation can either raise an error or flash a warning. If `types.errors` is set, the errors for type-validation will raise exceptions, whereas `types.user_error` raises exceptions for user-defined validation errors.

Each table attribute is a string-indexed table with a few fields:

1. `type`, where possible values are:
    + `STRING`
    + `NUMBER` (float)
    + `INTEGER`
    + `BOOLEAN`
    + `ARRAY` (integer-indexed table)
    + directly-passed Lua tables
    + `FUNCTION`
    + `USERDATA`
    + `ANY`
2. `validation`, a validation function that returns a boolean value
3. `error`, a boolean value that triggers an exception if the `validation` callback returns a `false` value (must have `require('stellar_types').user_error = true` enabled)
4. `default`, a default value in case of validation failure.

> Regarding the `default` value: it is validated both for type and user-defined validation at class creation, raising an error for failure. The `validation` callback is validated on class creation if `default` is set, raising an error for either failure or not returning a boolean. If `default` is not set, it will be validated on instance creation, raising either an warning with `nil` fallback, or error (if `types.user_error` is set to true).

```lua
Config = types.create_type('Config', {
    ['value'] = {
        ['type'] = types.STRING,
        ['validation'] = function(v) return #v > 0 end,
        ['error'] = true,
        ['default'] = 'default',
        ['nullable'] = true
    }
})
```

## Integration with Python

The `stellar_types` module is intended to be used with the `lupa` Python library. It is already compiled to be hydrated by the `lupa` Lua headers.

## Validating array-like tables

You can define the subtype of the array table using the user-defined validation:

```lua
ArrayType = types.create_type('Array', {
    ['arr'] = {
        ['type'] = types.ARRAY,
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

In theory, you can pass a simple Lua table to the `type` parameter, however, if you must work with array-like tables, uses `types.ARRAY`.

## Validating string-indexed tables

String-indexed tables are validated via their metatable (inheritance). You may use a StellarType or a regular table indexed by strings (dictionary). If the table is a regular dictionary, no metatable will be validated, which it means only user-defined validations will be performed.

```lua

PrimitiveType = types.create_type('Primitive', {
    attr = {
        type = types.STRING,
        validation = function(value)
            return #value > 0
        end
    }
})

primitive = PrimitiveTypetypes.STRING:new({
    attr = "value"
})

NestedType = types.create_type('Nested', {
    nested = {
        type = PrimitiveType,
        validation = function(value)
            return #value.attr < 10
        end
    }
})

nested = NestedType:new({
    nested = primitive
})

DictType = types.create_type('Dict', {
    dict = {
        type = {}, -- regular dictionary
        validation = function(v)
            return v.attr ~= nil
        end
    }
})

dictionary = DictType:new({
    dict = { attr = 'any' }
})
```

## Composite types

You may define a composite type using the user-defined validation:

```lua
CompositeType = types.create_type('Composite', {
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
-- example with lupa
types = require("stellar_types")

UserdataTypes = types.create_type('Udata', {
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

Python code (must be called so `python` module can work via `lupa`):

```python
import ctypes

import lupa.lua53 as lupa

ctypes.CDLL(lupa.__file__, mode=ctypes.RTLD_GLOBAL) # "hydrate" with Lua headers, dynamically

lua = lupa.LuaRuntime()

lua.globals()['complex'] = list()

lua.execute('dofile("./userdata_example.lua")')
```

## Integration with Python

As shown in the snippet above, you must use `lupa` and `ctypes` to "hydrate" the StellarTypes library files with the Lua headers. Integration is thought for creating Lua config files and scripting, leaving Python as a more static code.