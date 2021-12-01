#include <stdlib.h>
#include <stdio.h>

#include "errors.h"

// exit on error, print type error
void check_error(const error_t err)
{
    switch (err)
    {
    case NULL_PTR_ERROR:
        printf("NULL_PTR_ERROR - Попытка обращения к необьявленному указателю\n");
        exit(NULL_PTR_ERROR);

    case PARSE_ERROR:
        printf("PARSE_ERROR - Ошибка при вводе данных пользователем\n");
        exit(PARSE_ERROR);

    case PARSE_ACL_ERROR:
        printf("PARSE_ACL_ERROR - Ошибка преобразования аргументов коммандной строки\n");
        exit(PARSE_ACL_ERROR);
        
    default:
        printf("Неизвестная ошибка\n");
        exit(-1);
    }
}