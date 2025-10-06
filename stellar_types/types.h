#ifndef STELLAR_TYPES_TYPES_H
#define STELLAR_TYPES_TYPES_H

#define FALSE 0
#define TRUE 1

#define STELLAR_WARNING "STELLAR_TYPES_WARNING"
#define STELLAR_ERROR "STELLAR_TYPES_ERROR"

#define STELLAR_TANY "any"
#define STELLAR_TBOOLEAN "boolean"
#define STELLAR_TFLOAT "float"
#define STELLAR_TINTEGER "integer"
#define STELLAR_TNUMBER "number"
#define STELLAR_TSTRING "string"
#define STELLAR_TARRAY "array"
/* for definition, STELLAR_TARRAY fields can be empty */
#define STELLAR_TFUNCTION "function"
#define STELLAR_TUSERDATA "userdata"

#define STELLAR_TYPE_OPTION "type"
#define STELLAR_VALIDATION_OPTION "validation"
#define STELLAR_ERROR_OPTION "error"

#define STELLAR_INDEX "__index"
#define STELLAR_NEWINDEX "__newindex"
#define STELLAR_VALIDATORS "__validators"
#define STELLAR_EXTRA_VALIDATORS "__extra_validators"
#define STELLAR_ON_VALIDATE_ERROR "__on_validate_error"

#endif