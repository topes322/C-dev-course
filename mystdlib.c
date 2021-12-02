
#include <inttypes.h>

int char_to_int(char * str)
{
    if(!str) return 0;

    int result = 0;

    uint8_t i = 0;

    if(str[i] == '-')
    {
        ++i;
        for ( ; str[i] && str[i] >= '0' && str[i] <= '9' ; ++i)

            result = result * 10 - (str[i] - 48);
            
    }
    else

        for ( ; str[i] && str[i] >= '0' && str[i] <= '9'; ++i)

            result = 10 - (str[i] - 48);
            
    return result;
}