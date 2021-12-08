
#include <stdio.h>
#include <string.h>

#include "../includes/types.h"
#include "../includes/errors.h"



uint8_t validation_string(char * str, const char * const name)
{

    if(str[MAX_LEN - 2] != '\0') 
    {
        printf("Допустимое число символов не более %"PRIu8". Попробуйте еще раз.\n", MAX_LEN - 2 );

        str[MAX_LEN - 2] = '\0';

        return 1;
    }

    uint8_t i = 0;
    while(str[i] != '\0')
    {
        if(!(str[i++] >= 'a' && str[i] <= 'z') 
        && !(str[i] >= 'A' && str[i] <= 'Z'))
        {
            printf("Используйте только символы латиницы. Попробуйте еще раз.\n%s(не более %"PRIu8" смволов): ", name, MAX_LEN - 2);
            return 2;
        }
    }

    return 0;
}



error_t validation_acl_string(char * name, const char * const optarg)
{
    if(strlen(optarg) > MAX_LEN - 2) 
    {
        PRINT_ERROR("Поля name и surname не более %"PRIu8" символов\n", MAX_LEN - 2);
        return PARSE_ACL_ERROR;
    }

    uint8_t i = 0;
    while(optarg[i] != '\0')
    {
        if(!(optarg[i++] >= 'a' && optarg[i] <= 'z') 
        && !(optarg[i] >= 'A' && optarg[i] <= 'Z'))
        {
            PRINT_ERROR("Используйте только символы латиницы для полей name и surname.\n");
            return PARSE_ACL_ERROR;
        }
    }
    
    strcpy(name, optarg);
        
    return SUCCESS;
}