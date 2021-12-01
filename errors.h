
#ifndef _ERRORS_H_

#define _ERRORS_H_

#define ERROR_PLACE printf("File - %s, Func - %s, Line - %d\n", __FILE__, __FUNCTION__, __LINE__);

typedef enum error_t
{
    SUCSESS,
    NULL_PTR_ERROR,
    PARSE_ERROR, 
    PARSE_ACL_ERROR
} error_t;


void check_error(const error_t );


#endif