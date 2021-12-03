
#include <inttypes.h>


/*
*   Преобразует строку str в знаковое целое число num.
*
*   Возвращает -1 если обнаружены недопустимые символы.
*   -2 если произошло переполнение.
*   -3 если переданы пустые указатели.
*/
int string_to_int(int * num, char * str)
{
    if(!str || !num) return -3;

    int prev = 0;

    uint8_t i = 0;

    if(str[i] == '-')
    {
        ++i;
        for ( ; str[i] && str[i] >= '0' && str[i] <= '9' ; ++i)
        {
            *num = *num * 10 - (str[i] - 48);
            //printf("result = %d\tprev = %d\n", *num, prev);
            if(*num > prev) return -2;
            prev = *num;
        }

        if(str[i] != '\0') return -1;
    }
    else
    {

        for ( ; str[i] && str[i] >= '0' && str[i] <= '9'; ++i)
        {
            *num = *num * 10 + (str[i] - 48);
            //printf("result = %d\tprev = %d\n", *num, prev);
            if(*num < prev) return -2;
            prev = *num;
        }

        if(str[i] != '\0') return -1;
    }
            
    return 0;
}