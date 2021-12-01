
#ifndef _VALIDATION_STRING_H_

#define _VALIDATION_STRING_H_

#include <inttypes.h>
#include "types.h"
#include "errors.h"


uint8_t validation_string(char *, const char * const);


error_t validation_acl_string(char *, const char * const);


#endif