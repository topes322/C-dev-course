
#ifndef _FILE_H_

#define _FILE_H_

#include "types.h"
#include "errors.h"

#define FILE_NAME "person.bin"
#define REWRITE_MODE "w"
#define READ_MODE "r"

//static error_t read_file(person_t *);

//static error_t save_file(person_t *);


/*
*   Сохраняет струтуру person в конец файла в бинарном виде.
*   
*   Возвращает NULL_PTR_ERROR, если передан нулевой указатель person.
*              FILE_DESCRIPTOR_ERROR, если не удалось открыть или создать файл.
*              WRITE_FILE_ERROR, если не удалось записать в файл данные.
*              SUCCESS в случае успеха.
*/
error_t save_binary_data(person_t *);


/*
*   Читает файл в бинарном режиме, 
*   записывает в count число прочитанных структур person_t.  
*   
*   Сохраняет в err
*   FILE_DESCRIPTOR_ERROR, если не удалось открыть файл.
*   READ_FILE_ERROR, если не удалось прочитать файл.
*   NULL_PTR_ERROR, если не удалось выделить память.
*   SUCCESS в случае успеха.
*
*   Возвращает массив прочитаних из файла структур person_t.
*   В случае ошибки возвращает NULL.
*/
person_t * read_binary_data(int * count, error_t * err);




#endif