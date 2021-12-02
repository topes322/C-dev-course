
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "mystring.h"



/*
*   Открывает файл на запись. Перезаписывает данные в файл из person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае успеха возвращает 0.
*/
int save_file(person_t * person)
{
    FILE * file = fopen("person.txt", "w");
    if(!file) return -1;

    fprintf(file, "%s;%s;%"PRIu8";%"PRIu16";%"PRIu16";%"PRIu8,
    person->name, 
    person->surname, 
    person->age, 
    person->height, 
    person->weight, 
    person->gender );

    if(!ferror(file)) printf("Записано\n");

    fclose(file);

    return 0;
}


/*
*   Читает файл, преобразует и записывает данные в person.
*
*   В случает ошибки объявления дескриптора возвращает -1.
*   В случае успеха возвращает 0.
*/
int read_file(person_t * person)
{
    FILE * file = fopen("person.txt", "r");
    if(!file) return -1;

    char buffer[128];

    fgets(buffer,128,file);

    fclose(file);

    char * ptr = strtok(buffer, ";\n");

    // и моя функция и функция strtok копирует данные в стек 
    // размером примерно от 120 байт
    strcpy(person->name, ptr);

    ptr = strtok(NULL, ";\n");
    strcpy(person->surname, ptr);


    ptr = strtok(NULL, ";\n");
    person->age = (uint8_t)strtoul(ptr, NULL, 0);


    ptr = strtok(NULL, ";\n");
    person->height = (uint16_t)strtoul(ptr, NULL, 0);

    ptr = strtok(NULL, ";\n");
    person->weight = (uint16_t)strtoul(ptr, NULL, 0);


    ptr = strtok(NULL, ";\n");
    person->gender = (uint8_t)strtoul(ptr, NULL, 0);

    return 0;
}