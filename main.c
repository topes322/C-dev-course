#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

const uint8_t SIZE = 12U;

typedef enum error_t
{
    SUCSESS,
    NULL_PTR_ERROR,
    PARSE_ERROR
} error_t;


typedef enum gender_t {
    UNDEFINED,
    MALE,
    FEMALE
} gender_t;


typedef struct person_t
{
    char name[64];
    char surname[64]; 
    uint8_t age;
    uint16_t height;
    uint16_t weight; 
    gender_t gender;
} person_t;



error_t print_personal_data(const person_t*);

error_t get_personal_data(person_t*);

error_t validation_string(char*);

void check_error(err);

error_t parse_command_line_arg(person_t*, int, char*[]);



int main(int argc, char* argv[])
{
    person_t person = {{'\0'}, {'\0'}, 0 , 0 , 0, UNDEFINED };

    __CHAR16_TYPE__ q = L'a';
    printf("%u\n", q);
    if(argc > 1)
    {
        for (uint8_t i = 0; i < argc; i++)
        {
            printf("argc #%u: %s\n", i, argv[i]);
        }
        
    char *opts = "aa:b:o:"; // доступные опции, каждая принимает аргумент
    int opt; // каждая следующая опция попадает сюда
    while((opt = getopt(argc, argv, opts)) != -1) { // вызываем getopt пока она не вернет -1
    printf("%d\n", opt);
        switch(opt) {
            case 'a': // если опция -a, преобразуем строку с аргументом в число
                printf("-a switch\n");
                break;
             case 'b': // тоже для -b
                 
                 break;
             case 'o': // в op сохраняем оператор
                 
                 break;
             default:
                printf("def ./a.out\n");
                break;
        }
    }

    }
    else
    {
        error_t err = get_personal_data(&person);
        if(err != SUCSESS) check_error(err);

        print_personal_data(&person);
    }


    /*
    // unicode для кирилицы 

        union test_t
    {
        unsigned char str[3];
        uint16_t byte;
    } test_t;
    scanf("%s", &test_t.str);
    printf("strlen = %d\n", strlen(test_t.str));
    printf("byte2 = %u\n", test_t.byte);
    printf("string = %s\n", test_t.str);
    */
/*
    // аргументы командной строки
    unsigned char a = 'а',b = 'я';
    printf("%u %u\n", a,b);
    unsigned char aa = 'a',bb = 'z';
    printf("%u %u\n", aa,bb);
    printf("%d\n", argc);
    */

    return 0;
}



// user enter data into struct person_t
error_t get_personal_data(person_t* data)
{
    if(!data) return NULL_PTR_ERROR;
    error_t err = SUCSESS;

    printf("Введите данные:\nИмя(не более 62 смволов): ");
    err = validation_string(data->name);
    if(!err) return err;
    
    ///
    
    printf("Фамилия(не более 62 смволов): ");
    do
    {

        err = validation_string(data->surname);
        if(!err) return err;

        uint8_t flag = 0;

        if(data->surname[SIZE - 2] != '\0') 
        {
            flag++;
            printf("Допустимое число символов не более 62. Попробуйте еще раз.\n");
        }
        data->surname[SIZE - 2] = '\0';

        uint8_t i = 0;
        while(data->surname[i] != '\0')
        {
            /*
            printf("%c - %d\n", data->second_name[i], data->second_name[i]);
            printf("%c - %d\n", 'a','a' );
            printf("%c - %d\n", 'z','z');
            printf("%c - %d\n", 'A','A');
            printf("%c - %d\n", 'Z','Z');
            printf("%d\n", data->second_name[i] < 'a' || data->second_name[i] > 'z' &
               data->second_name[i] < 'A' || data->second_name[i] > 'Z');*/

            if(!(data->surname[i] >= 'a' && data->surname[i] <= 'z') 
            && !(data->surname[i] >= 'A' && data->surname[i] <= 'Z')
            //&& !(data->second_name[i] >= 'а' && data->second_name[i] <= 'я')
            //&& !(data->second_name[i] >= 'А' && data->second_name[i] <= 'Я')
            // а = 45264 - 2 bytes
            // А = 37072 
            // я = 36817 
            )
            {
               flag++;
               //printf("flag set\n");
               break;
            }
            i++;
        }

        if(flag == 0) break;
        flag = 0;
    } while (1);
    
    
    //
    printf("Возраст(от 18 до 125): ");
    do
    {
        if(scanf("%"PRIu8, &data->age) != 1) return PARSE_ERROR;

        if(data->age < 18 || data->age > 125)
            printf("Введен некорректный возраст. Вы ввели %"PRIu8"\nНеобходимо ввести возраст от 18 до 125 лет\nПопробуйте снова\n", data->age);

    } while (data->age < 18 || data->age > 125);
    
    //
    printf("Рост: ");
    if(scanf("%"PRIu16, &data->height) != 1) return PARSE_ERROR;

    //
    printf("Вес: ");
    if(scanf("%"PRIu16, &data->weight) != 1) return PARSE_ERROR;

    //
    printf("Выберите ваш пол(Мужской - 1, Женский - 2): ");
    do
    {   
        data->gender = UNDEFINED;
        if(scanf("%"PRIu8, &data->gender) != 1) return PARSE_ERROR;
        if(data->gender > FEMALE)
            printf("Некорректно введены данные. Попробуйте снова.\nМужской - 1, Женский - 2\nВы ввели: %u\n", data->gender);
    } while(data->gender > FEMALE);
    return SUCSESS;
}



error_t validation_string(char * str)
{
    if(!str) return NULL_PTR_ERROR;

    if(scanf("%63s", str) != 1) return PARSE_ERROR;
}


// parse command line arguments
// prompt for user input if there is not enough data
error_t parse_command_line_arg(person_t* p, int argc, char* argv[])
{
    //getopt -fn -ln -age -len -w -gen
    //-n -s -a -l -w -g
    
}


// print data struct person_t
error_t print_personal_data(const person_t * p)
{
    if(!p) return NULL_PTR_ERROR;
    printf("\nИмя: %s\n", p->name);
    printf("Фамилия: %s\n", p->surname);

    printf("Возраст: %hhu\n" , p->age);
    printf("Рост: %hu\n" , p->height);
    printf("Вес: %hu\n", p->weight);

    printf("Пол: ");
    switch (p->gender)
    {
    case UNDEFINED:
        printf("Не определено\n");
        break;
    case MALE:
        printf("Мужской\n");
        break;
    case FEMALE:
        printf("Женский\n");
        break;
    
    default:
        printf("Неизвестно\n");
        break;
    }
}


void check_error(error_t err)
{
    switch (err)
    {
    case NULL_PTR_ERROR:
        printf("Попытка обращения к необьявленному указателю\n");
        exit(NULL_PTR_ERROR);
    case PARSE_ERROR:
        printf("Ошибка при вводе данных пользователем\n");
        exit(PARSE_ERROR);
    default:
        printf("Неизвестная ошибка\n");
        exit(-1);
        break;
    }
}