
#ifndef _GETTERS_H_

#define _GETTERS_H_

#include "types.h"
#include <inttypes.h>


error_t get_personal_data(person_t*);


error_t get_name(char * , const char * const);


error_t get_age(uint8_t*);


error_t get_height(uint16_t*);


error_t get_weight(uint16_t*);


error_t get_gender(gender_t*);


#endif