
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/types.h"
#include "../includes/errors.h"

#include "../includes/file.h"



/*
*   Открывает файл на запись. Перезаписывает данные в файл из person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае ошибки записи возвращает -2.
*   В случае успеха возвращает 0.
*/
static error_t save_file(person_t * person)
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

    return SUCCESS;
}


/*
*   Читает файл, преобразует и записывает данные в person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае ошибки чтения возвращает -3.
*   В случае успеха возвращает 0.
*/
static error_t read_file(person_t * person)
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

    return SUCCESS;
}


//////// binary //////////


/*
*   Сохраняет струтуру person в конец файла в бинарном виде.
*   
*   Возвращает NULL_PTR_ERROR, если передан нулевой указатель person.
*              FILE_DESCRIPTOR_ERROR, если не удалось открыть или создать файл.
*              WRITE_FILE_ERROR, если не удалось записать в файл данные.
*              SUCCESS в случае успеха.
*/
error_t save_binary_data(person_t * person)
{
    if(!person)
    {
        PRINT_ERROR("Не передан аргумент person\n");
        return NULL_PTR_ERROR;
    }

    FILE * file = fopen(FILE_NAME, "ab");
    if(!file) 
    {
       PRINT_ERROR("Не удалось открыть файл: %s\n", FILE_NAME);
       return FILE_DESCRIPTOR_ERROR;
    }
    

    if(fwrite(person, sizeof(person_t), 1, file) != 1)
    {
        PRINT_ERROR("Ошибка записи стуктуры person в файл %s\n", FILE_NAME);
        return WRITE_FILE_ERROR;
    }

    fclose(file);

    return SUCCESS;
}



person_t * read_binary_data(int * count, error_t * err)
{

    if(!count || !err)
    {
        PRINT_ERROR("Переданы не все аргументы\n");
        *err = NULL_PTR_ERROR;
        return NULL;
    }

    FILE * file = fopen(FILE_NAME, "rb");
    if(!file) 
    {
       PRINT_ERROR("Не удалось открыть файл: %s\n", FILE_NAME);

       *err = FILE_DESCRIPTOR_ERROR;
       return NULL;
    }

    *count = 0;

    fseek(file, 0, SEEK_END);
    *count = ftell(file) / sizeof(person_t);

    fseek(file, 0, SEEK_SET);

    if(*count == 0)
    {
        *err = SUCCESS;
        return NULL;
    }

    person_t * person = malloc(sizeof(person_t) * *count);

    if(!person)
    {
        PRINT_ERROR("Не удалось выделить память\n");
        *err = NULL_PTR_ERROR;
        return NULL;
    }
    
    if(fread(person, sizeof(person_t), *count, file) != *count)
    {
        PRINT_ERROR("Ошибка чтения стуктуры person из файла %s\n", FILE_NAME);
        fclose(file);

        *err = WRITE_FILE_ERROR;
        return NULL;
    }

    fclose(file);
    
    *err = SUCCESS;
    return person;
}


