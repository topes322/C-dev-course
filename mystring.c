#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "mystring.h"

extern char * string = NULL;

char * mystrtok(char * str, const char delimiter)
{   
    //static char * string = NULL;

    if(!str && !string) return NULL;
    
    if(str && !string) string = str;

    char * new_string = malloc(strlen(string));

    uint8_t i = 0;

    do
    {
        for ( ; *string && *string != delimiter; ++string, ++i)
            new_string[i] = *string;

        if(*string == delimiter) 
            ++string;

        if(*string == '\0') 
            break;

    } while ( i == 0 );
    
    
    new_string[i] = '\0';

    if( !*string ) 
        string = NULL;

    else if (*(string - 1) == delimiter)
        realloc(new_string, strlen(new_string + 1));
   
    return new_string;
}