#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_LEN 12U

typedef enum error_t
{
    SUCSESS,
    NULL_PTR_ERROR,
    PARSE_ERROR, 
    PARSE_ACL_ERROR
} error_t;


typedef enum gender_t {
    UNDEFINED,
    MALE,
    FEMALE
} gender_t;


typedef struct person_t
{
    char name[MAX_LEN];
    char surname[MAX_LEN]; 
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


error_t get_name(char*, char*);

error_t get_age(uint8_t*);

error_t get_height(uint16_t*);

error_t get_weight(uint16_t*);

error_t get_gender(gender_t*);


error_t validation_acl_string(char *, char *);



int main(int argc, char* argv[])
{
    person_t person = {{'\0'}, {'\0'}, 0 , 0 , 0, UNDEFINED };


    if(argc > 1)
    {

        error_t err = parse_command_line_arg(&person, argc, argv);
        if(err != SUCSESS) check_error(err);
    }
    else
    {
        error_t err = get_personal_data(&person);
        if(err != SUCSESS) check_error(err);
    }

    print_personal_data(&person);

    return 0;
}



// user enter data into struct person_t
error_t get_personal_data(person_t* data)
{
    if(!data) return NULL_PTR_ERROR;
    error_t err = SUCSESS;


    err = get_name(data->name, "Имя");
    if(err != 0) return err;

    err = get_name(data->surname, "Фамилия");
    if(err != 0) return err;

    //   
    err = get_age(&data->age);
    if(err != 0) return err;
    
    //
    err = get_height(&data->height);
    if(err != 0) return err;
    
    //
    err = get_weight(&data->weight);
    if(err != 0) return err;
    
    //
    err = get_gender(&data->gender);
    if(err != 0) return err;
    

    return SUCSESS;
}



// parse command line arguments
// prompt for user input if there is not enough data
error_t parse_command_line_arg(person_t* p, int argc, char* argv[])
{

    const char* short_options = "n:s:a:h:w:g:";
    
	const struct option long_options[] = {
		{"name", required_argument, NULL, 'n'},
		{"surname", required_argument, NULL, 's'},
		{"age", required_argument, NULL, 'a'},
        {"height", required_argument, NULL, 'h'},
        {"weight", required_argument, NULL, 'w'},
        {"gender", required_argument, NULL, 'g'},
        {"help", no_argument, NULL, 1},
		{NULL, 0, NULL, 0}
	};

	int option;
	int option_index;

    while ((option = getopt_long(  argc, argv, 
                                short_options,
		                        long_options, 
                                &option_index)) != -1)
    {

		switch(option){
			case 'n': // name
            {
				if (optarg)
                {
                    error_t err = validation_acl_string(p->name, optarg);
                    if(err != SUCSESS) return err;
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };

			case 's': // surname
            {
				if (optarg)
                {
                    error_t err = validation_acl_string(p->surname, optarg);
                    if(err != SUCSESS) return err;
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
			};
	
			case 'a': // age
            {
                if (optarg)
                {

                    int i = 0; 
                    while(optarg[i] != '\0') 
                        if( optarg[i++] < '0' || optarg[i] > '9' )
                        { 
                            printf("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
                            return PARSE_ACL_ERROR;
                        }
                    
                    int temp = atoi(optarg);
                    if(temp < 18 || temp > 125) 
                    {
                        printf("Возраст от 18 до 125. Введено: %d\n", temp);
                        return PARSE_ACL_ERROR;
                    }

                    p->age = (uint8_t)temp;
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
				break;
			};

            case 'h': // height
            {
                if(optarg)
                {
                    int i = 0; 
                    while(optarg[i] != '\0') 
                        if( optarg[i++] < '0' || optarg[i] > '9' ) 
                        { 
                            
                            printf("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
                            return PARSE_ACL_ERROR;
                        }

                    int temp = atoi(optarg);
                    if(temp < 10 || temp > 500) 
                    {
                        printf("Рост от 10 до 500. Введено: %d\n", temp);
                        return PARSE_ACL_ERROR;
                    }
                    printf("Height\n");
                    p->height = (uint16_t)temp;
                    printf("%u\n", p->height);
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };

            case 'w': // weight
            {
                if(optarg)
                {
                    int i = 0; 
                    while(optarg[i] != '\0') 
                    {
                        if( optarg[i++] < '0' || optarg[i] > '9' ) 
                        { 
                            printf("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
                            return PARSE_ACL_ERROR;
                        }
                    }


                    p->weight = (uint16_t)atoi(optarg);
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };

            case 'g': // gender
            {
                if (optarg)
                {
                    int i = 0; 

                        while(optarg[i] != '\0') 
                            if( optarg[i++] < '0' || optarg[i] > '9' ) 
                            { 
                                printf("Недопустимые символы\n");
                                return PARSE_ACL_ERROR;
                            }

                        int temp = atoi(optarg);
                        if(temp < UNDEFINED || temp > FEMALE) 
                        {
                            printf("Неверно указан пол. Мужской - 1, Женский - 2. Введено: %d\n", temp);
                            return PARSE_ACL_ERROR;
                        }
                        p->gender = (uint8_t)temp;
                }
                else
                {
                    printf("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };
            
            case 1: 
            {
				printf( "Можете запустить программу без аргументов и ввести данные вручную\n"
                        "Список доступных аргументов командной строки:\n"
                        "-n YourName или --name YourName , имя латиницей не более %u символов\n"
                        "-s YourSurname или --surname YourSurname , фамилия латинцей не более %u символов\n"
                        "-a 20 или --age 20 , ваш возраст, от 18 до 125 лет\n"
                        "-h 180 или --height 180 , ваш рост, целое число, от 10 до 500\n"
                        "-w 80 или --weight 80 , ваш вес, целое число, от 10 до 500\n"
                        "-g 1 или --gender 1 , ваш пол, целое число, Мужской - 1, Женский - 2\n"
                        , MAX_LEN - 2 , MAX_LEN - 2);
				break;
			};

			case '?': default: {
				printf("found unknown option or not found argument\n");
                return PARSE_ACL_ERROR;
                break;
			};
		};
	};

    error_t err = SUCSESS;
    
    // check parse args
    if(p->name[0] == '\0')
    {
        err = get_name(p->name, "Имя");

        if(err != SUCSESS) check_error(err);
    }

    if(p->surname[0] == '\0')
    {
        err = get_name(p->surname, "Фамилия");

        if(err != SUCSESS) check_error(err);
    }

    if(p->age == 0) 
    {
        err = get_age(&p->age);
        if(err != SUCSESS) check_error(err);
    }

    printf("if %u\n", p->height);
    if(p->height == 0) 
    {   
        err = get_height(&p->height);
        if(err != SUCSESS) check_error(err);
    }

    if(p->weight == 0) 
    {
        err = get_weight(&p->weight);
        if(err != SUCSESS) check_error(err);
    }

    if(p->gender == UNDEFINED || p->gender > FEMALE) 
    {
        err = get_gender(&p->gender);
        if(err != SUCSESS) check_error(err);
    }

    return SUCSESS;
}


error_t validation_acl_string(char * name, char * optarg)
{
    if(strlen(optarg) > MAX_LEN - 2) 
    {
        printf("Поля name и surname не более %u символов\n", MAX_LEN - 2);
        return PARSE_ACL_ERROR;
    }

    uint8_t i = 0;
    while(optarg[i] != '\0')
    {
        if(!(optarg[i] >= 'a' && optarg[i] <= 'z') 
        && !(optarg[i] >= 'A' && optarg[i] <= 'Z'))
        {
            printf("Используйте только символы латиницы для полей name и surname.\n");
            return PARSE_ACL_ERROR;
        }
        i++;
    }
    
    strcpy(name, optarg);
        
    return SUCSESS;
}

error_t get_name(char* name, char* n)
{
    uint8_t err = SUCSESS;
    printf("%s(латиницей, не более %u смволов): ", n, MAX_LEN - 2);
    while (1)
    {

        err = validation_string(name);
        if(!err) return err;

        uint8_t flag = 0;

        if(name[MAX_LEN - 2] != '\0') 
        {
            flag++;
            printf("Допустимое число символов не более %u. Попробуйте еще раз.\n", MAX_LEN - 2 );
            uint8_t i = 0;
            while (name[i] != '\0') name[i++] = '\0';
        }

        uint8_t i = 0;
        while(name[i] != '\0')
        {

            if(!(name[i] >= 'a' && name[i] <= 'z') 
            && !(name[i] >= 'A' && name[i] <= 'Z'))
            {
               flag++;
               printf("Испльзуйте только символы латиницы. Попробуйте еще раз.\n%s(не более %u смволов): ", n, MAX_LEN - 2);
               break;
            }
            i++;
        }

        if(flag == 0) break;
        flag = 0;
    } // while(1)
    return SUCSESS;
}


error_t get_age(uint8_t * age)
{
    do
    {
        printf("Возраст(целое число от 18 до 125): ");
        if(scanf("%"PRIu8, age) != 1) return PARSE_ERROR;
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
        if(scanf("%"PRIu16, height) != 1) return PARSE_ERROR;

        if(*height < 10 || *height > 500)
            printf("\nВведен некорректный рост. Вы ввели %"PRIu8"\nНеобходимо ввести рост от 10 до 500\nПопробуйте снова\n", *height);

    } while(*height < 10 || *height > 500);
    return SUCSESS;
}


error_t get_weight(uint16_t * weight)
{
    do
    {
        printf("Вес кг(целое число от 10 до 500): ");
        if(scanf("%"PRIu16, weight) != 1) return PARSE_ERROR;

        if(*weight < 10 || *weight > 500)
                printf("\nВведен некорректный вес. Вы ввели %"PRIu8"\nНеобходимо ввести вес от 10 до 500\nПопробуйте снова\n", *weight);

    } while(*weight < 10 || *weight > 500);
    return SUCSESS;
}

error_t get_gender(gender_t * gender)
{
    do
    {   
        printf("Выберите ваш пол(Мужской - 1, Женский - 2): ");
        *gender = UNDEFINED;
        if(scanf("%"PRIu8, gender) != 1) return PARSE_ERROR;
        if(*gender > FEMALE)
            printf("\nНекорректно введены данные. Попробуйте снова.\nМужской - 1, Женский - 2\nВы ввели: %u\n", *gender);
    } while(*gender > FEMALE);
    return SUCSESS;
}


error_t validation_string(char * str)
{
    if(!str) return NULL_PTR_ERROR;
    // MAX_LEN - 1
    if(scanf("%11s", str) != 1) return PARSE_ERROR;

    return SUCSESS;
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

    return SUCSESS;
}

// exit on error, print type error
void check_error(error_t err)
{
    switch (err)
    {
    case NULL_PTR_ERROR:
        printf("NULL_PTR_ERROR Попытка обращения к необьявленному указателю\n");
        exit(NULL_PTR_ERROR);
    case PARSE_ERROR:
        printf("PARSE_ERROR Ошибка при вводе данных пользователем\n");
        exit(PARSE_ERROR);
    case PARSE_ACL_ERROR:
        printf("PARSE_ACL_ERROR Ошибка преобразования аргументов коммандной строки\n");
        exit(PARSE_ACL_ERROR);
    default:
        printf("Неизвестная ошибка\n");
        exit(-1);
        break;
    }
}