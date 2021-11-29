
#include "types.h"

#include <stdio.h>
#include <string.h>


error_t validation_string(char * str)
{
    if(!str) return NULL_PTR_ERROR;
    // MAX_LEN - 1
    if(scanf("%11s", str) != 1) return PARSE_ERROR;

    return SUCSESS;
}


error_t validation_acl_string(char * name, char * optarg)
{
    if(strlen(optarg) > MAX_LEN - 2) 
    {
        printf("Поля name и surname не более %"PRIu8" символов\n", MAX_LEN - 2);
        return PARSE_ACL_ERROR;
    }

    uint8_t i = 0;
    while(optarg[i] != '\0')
    {
        if(!(optarg[i++] >= 'a' && optarg[i] <= 'z') 
        && !(optarg[i] >= 'A' && optarg[i] <= 'Z'))
        {
            printf("Используйте только символы латиницы для полей name и surname.\n");
            return PARSE_ACL_ERROR;
        }
    }
    
    strcpy(name, optarg);
        
    return SUCSESS;
}