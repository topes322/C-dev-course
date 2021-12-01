
#ifndef _TYPES_H_

#define _TYPES_H_

#include <inttypes.h>

#define MAX_LEN 12U


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