#include <stdlib.h>
#include <stdio.h>

#include "../includes/errors.h"

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

    case FILE_DESCRIPTOR_ERROR:
        printf("FILE_DESCRIPTOR_ERROR - Ошибка при получении файлового дескриптора\n");
        exit(FILE_DESCRIPTOR_ERROR);

    case WRITE_FILE_ERROR:
        printf("WRITE_FILE_ERROR - Ошибка при записи в файл\n");
        exit(WRITE_FILE_ERROR);

    case READ_FILE_ERROR:
        printf("READ_FILE_ERROR - Ошибка при чтении файла\n");
        exit(READ_FILE_ERROR);
        
    default:
        printf("Неизвестная ошибка\n");
        exit(-1);
    }
}