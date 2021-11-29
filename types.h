
#ifndef _HEADER_H_

#define _HEADER_H_

#include <inttypes.h>

#define MAX_LEN 12U

typedef enum error_t
{
    SUCSESS,
    NULL_PTR_ERROR,
    PARSE_ERROR, 
    PARSE_ACL_ERROR
} error_t;


typedef enum gender_t {
    UNDEFINED,
    MALE,
    FEMALE
} gender_t;


typedef struct person_t
{
    char name[MAX_LEN];
    char surname[MAX_LEN]; 
    uint8_t age;
    uint16_t height;
    uint16_t weight; 
    gender_t gender;
} person_t;

#endif