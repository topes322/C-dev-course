#include <stdio.h>

#include "getters.h"
#include "types.h"
#include "errors.h"



// user enter data into struct person_t
error_t get_personal_data(person_t* data)
{
    if(!data) return NULL_PTR_ERROR;
    error_t err = SUCSESS;


    err = get_name(data->name, "Имя");
    if(err) return err;

    err = get_name(data->surname, "Фамилия");
    if(err) return err;

    //   
    err = get_age(&data->age);
    if(err) return err;
    
    //
    err = get_height(&data->height);
    if(err) return err;
    
    //
    err = get_weight(&data->weight);
    if(err) return err;
    
    //
    err = get_gender(&data->gender);
    if(err) return err;
    

    return SUCSESS;
}



error_t get_name(char * str, const char * const name)
{
    do
    {
        printf("%s(латиницей, не более %u смволов): ", name, MAX_LEN - 2);

        if(!str || !name)
        {
            ERROR_PLACE;
            return NULL_PTR_ERROR;
        }

        // MAX_LEN - 1
        if(scanf("%11s", str) != 1) 
        {
            ERROR_PLACE;
            return PARSE_ERROR;
        }
    }
    while (validation_string(str, name));

    return SUCSESS;
}



error_t get_age(uint8_t * age)
{
    do
    {
        printf("Возраст(целое число от 18 до 125): ");

        if(scanf("%"PRIu8, age) != 1) 
        {
            ERROR_PLACE;
            return PARSE_ERROR;
        }

        if(*age < 18 || *age > 125)
            printf("\nВведен некорректный возраст. Вы ввели %"PRIu8"\nНеобходимо ввести возраст от 18 до 125 лет\nПопробуйте снова\n", *age);

    } while (*age < 18 || *age > 125);

    return SUCSESS;
}



error_t get_height(uint16_t * height)
{
    do
    {
        printf("Рост см(целое число от 10 до 500): ");

        if(scanf("%"PRIu16, height) != 1) 
        {
            ERROR_PLACE;
            return PARSE_ERROR;
        }

        if(*height < 10 || *height > 500)
            printf("\nВведен некорректный рост. Вы ввели %"PRIu16"\nНеобходимо ввести рост от 10 до 500\nПопробуйте снова\n", *height);

    } while(*height < 10 || *height > 500);

    return SUCSESS;
}



error_t get_weight(uint16_t * weight)
{
    do
    {
        printf("Вес кг(целое число от 10 до 500): ");

        if(scanf("%"PRIu16, weight) != 1) 
        {
            ERROR_PLACE;
            return PARSE_ERROR;
        }

        if(*weight < 10 || *weight > 500)
                printf("\nВведен некорректный вес. Вы ввели %"PRIu16"\nНеобходимо ввести вес от 10 до 500\nПопробуйте снова\n", *weight);

    } while(*weight < 10 || *weight > 500);

    return SUCSESS;
}



error_t get_gender(gender_t * gender)
{
    do
    {   
        printf("Выберите ваш пол(Мужской - 1, Женский - 2): ");

        *gender = UNDEFINED;
        if(scanf("%"PRIu8, gender) != 1) 
        {
            ERROR_PLACE;
            return PARSE_ERROR;
        }

        if(*gender > FEMALE)
            printf("\nНекорректно введены данные. Попробуйте снова.\nМужской - 1, Женский - 2\nВы ввели: %"PRIu8"\n", *gender);

    } while(*gender > FEMALE);

    return SUCSESS;
}


