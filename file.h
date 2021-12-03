
#ifndef _FILE_H_

#define _FILE_H_

#include "types.h"
#include "errors.h"

#define FILE_NAME "person.txt"
#define REWRITE_MODE "w"
#define READ_MODE "r"

error_t read_file(person_t *);

error_t save_file(person_t *);

#endif