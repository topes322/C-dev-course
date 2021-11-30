#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <getopt.h> 

#include "types.h"
#include "getters.h"
#include "validation_str.h"




error_t print_personal_data( const person_t* const );


error_t parse_command_line_arg(person_t*, const  int, const  char * const []);


void check_error(error_t const);



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



// parse command line arguments
// prompt for user input if there is not enough data
error_t parse_command_line_arg(person_t * p, const int argc, const char * const argv[])
{
    uint16_t height = 0;
    uint16_t weight = 0;

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
                    
                    height = (uint16_t)temp;
                    
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

                    int temp = atoi(optarg);
                    if(temp < 10 || temp > 500) 
                    {
                        printf("Вес от 10 до 500. Введено: %d\n", temp);
                        return PARSE_ACL_ERROR;
                    }
                    
                    weight = (uint16_t)temp;
                    
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
                                printf("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
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
                        "-n YourName или --name YourName , имя латиницей не более %"PRIu8" символов\n"
                        "-s YourSurname или --surname YourSurname , фамилия латинцей не более %"PRIu8" символов\n"
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

    
    if(height == 0) 
    {   
        err = get_height(&p->height);
        if(err != SUCSESS) check_error(err);
    }
    else p->height = height;
    
    if(weight == 0) 
    {
        err = get_weight(&p->weight);
        if(err != SUCSESS) check_error(err);
    }
    else p->weight = weight;

    if(p->gender == UNDEFINED || p->gender > FEMALE) 
    {
        err = get_gender(&p->gender);
        if(err != SUCSESS) check_error(err);
    }

    return SUCSESS;
}



// print data struct person_t
error_t print_personal_data(const person_t * const p)
{
    if(!p) return NULL_PTR_ERROR;

    printf("\nИмя: %s\n", p->name);
    printf("Фамилия: %s\n", p->surname);

    printf("Возраст: %"PRIu8"\n" , p->age);
    printf("Рост: %"PRIu16"\n" , p->height);
    printf("Вес: %"PRIu16"\n", p->weight);

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
void check_error(error_t const err)
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