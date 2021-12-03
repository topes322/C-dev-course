#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "mystring.h"



/*
*   Делит строку на подстроки символом-разделителем. Аналог strtok.
*   Для первого вызова подаются оба аргумента. Для последующих в аргумент str передается NULL. 
*   str - строка для деления, delimiter - символ-разделитель.
*
*   Возвращает указатель на новую подстроку в случае нахождения разделителя.
*   После возврата последней подстроки и нахождения нуль-символа возвращает нулевой указатель.
*/
char * mystrtok(char * str, const char delimiter)
{   

    static char * string = NULL;

    if(str == NULL && string == NULL)
    {
        //printf("return NULL\n"); 
        return NULL;
    }

    if(str != NULL) 
        string = str;



    char * new_string = malloc(strlen(string) + 1);
    //printf("strlen(string) = %d\n", strlen(string));

    uint16_t i = 0;
    
    do
    {
        for(; *string != '\0' && *string != delimiter; ++string, ++i)
        {
            new_string[i] = *string;
            //printf("%c\t %d\n", new_string[i], i);
        }
        if (*string == delimiter) ++string;
        if (*string == '\0') break;
    } while (i == 0);
        

    if(*string == '\0')
        string = NULL;
    
    new_string[i] = '\0';

   
    return new_string;
}



int string_copy(char * dest, char * sourse)
{

    uint16_t i = 0;

    for(; *sourse ; ++i)
    {
        
        dest[i] = sourse[i];
        printf("%c\n", dest[i]);
    }
    
    dest[++i] = '\0';

    return 0;
}