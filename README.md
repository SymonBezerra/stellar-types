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

## Validating array-like tables

## Validating object-like tables

## Function values

## Userdata values