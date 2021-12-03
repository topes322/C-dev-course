
#ifndef _ERRORS_H_

#define _ERRORS_H_

//#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define PRINT_ERROR(...) printf("File - %s, Func - %s, Line - %d\n", __FILE__, __FUNCTION__, __LINE__); \
                         fprintf(stderr, __VA_ARGS__);

typedef enum error_t
{
    SUCSESS,
    NULL_PTR_ERROR,
    PARSE_ERROR, 
    PARSE_ACL_ERROR,
    FILE_DESCRIPTOR_ERROR,
    WRITE_FILE_ERROR,
    READ_FILE_ERROR
} error_t;


void check_error(const error_t );


#endif