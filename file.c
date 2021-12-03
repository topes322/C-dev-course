
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "mystring.h"
#include "errors.h"

#include "file.h"



/*
*   Открывает файл на запись. Перезаписывает данные в файл из person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае ошибки записи возвращает -2.
*   В случае успеха возвращает 0.
*/
error_t save_file(person_t * person)
{
    FILE * file = fopen(FILE_NAME, REWRITE_MODE);
    if(!file) 
    {
        PRINT_ERROR("Ошибка обявления дескриптора файла: %s\n", FILE_NAME);
        return FILE_DESCRIPTOR_ERROR;
    }

    fprintf(file, "%s;%s;%"PRIu8";%"PRIu16";%"PRIu16";%"PRIu8,
    person->name, 
    person->surname, 
    person->age, 
    person->height, 
    person->weight, 
    person->gender );

    if(ferror(file)) 
    {
        PRINT_ERROR("Ошибка записи в файл: %s\n", FILE_NAME);
        return WRITE_FILE_ERROR;
    }
    

    fclose(file);

    return SUCSESS;
}


/*
*   Читает файл, преобразует и записывает данные в person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае ошибки чтения возвращает -3.
*   В случае успеха возвращает 0.
*/
error_t read_file(person_t * person)
{
    FILE * file = fopen(FILE_NAME, READ_MODE);
    if(!file) 
    {
       PRINT_ERROR("Ошибка обявления дескриптора файла: %s\n", FILE_NAME);
       return FILE_DESCRIPTOR_ERROR;
    }

    char buffer[128];

    if(!fgets(buffer,128,file))
    {
        PRINT_ERROR("Ошибка чтения файла: %s\n", FILE_NAME);
        return READ_FILE_ERROR;
    }

    fclose(file);



    char * ptr = strtok(buffer, ";\n");

    // и моя функция и функция strtok копирует данные в стек 
    // размером примерно от 120 байт
    if(ptr) strcpy(person->name, ptr);

    ptr = strtok(NULL, ";\n");
    if(ptr) strcpy(person->surname, ptr);


    ptr = strtok(NULL, ";\n");
    if(ptr) person->age = (uint8_t)strtoul(ptr, NULL, 0);


    ptr = strtok(NULL, ";\n");
    if(ptr) person->height = (uint16_t)strtoul(ptr, NULL, 0);

    ptr = strtok(NULL, ";\n");
    if(ptr) person->weight = (uint16_t)strtoul(ptr, NULL, 0);


    ptr = strtok(NULL, ";\n");
    if(ptr) person->gender = (uint8_t)strtoul(ptr, NULL, 0);

    return SUCSESS;
}