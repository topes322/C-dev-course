#include <stdio.h>
#include <inttypes.h>
#include <getopt.h> 
#include <stdlib.h>

#include "../includes/types.h"
#include "../includes/getters.h"
#include "../includes/validation_string.h"
#include "../includes/errors.h"
#include "../includes/file.h"

#include "../includes/mystdlib.h"
#include "../includes/mystring.h"


error_t print_personal_data( const person_t* const );


error_t parse_command_line_arg(person_t*, const  int, const  char * const []);



int main(int argc, char* argv[])
{

    /*char * text = ";12;34;;3245;432;";
    
    char * s = mystrtok( text, ';');
    

    while(s)
    {
        printf("%s\n", s);
        
        s = mystrtok(NULL, ';');
    }
    free(s);*/

    // *****

    person_t person = {{'\0'}, {'\0'}, 0 , 0 , 0, UNDEFINED };


    if(argc > 1)
    {
        error_t err = parse_command_line_arg(&person, argc, argv);
        if(err != SUCCESS) check_error(err);
    }
    /*else
    {
        error_t err = get_personal_data(&person);
        if(err != SUCCESS) check_error(err);
        
        err = save_binary_data(&person);
        if(err) check_error(err);

        print_personal_data(&person);
    }*/

    return 0;
}



// parse command line arguments
// prompt for user input if there is not enough data
error_t parse_command_line_arg(person_t * p, const int argc, const char * const argv[])
{
    uint16_t height = 0;
    uint16_t weight = 0;
    uint8_t flag_add = 0;
    uint8_t flag_print = 0;

    const char* short_options = "n:s:a:h:w:g:";
    
	const struct option long_options[] = {
		{"name",    required_argument, NULL, 'n'},
		{"surname", required_argument, NULL, 's'},
        {"age",     required_argument, NULL, 'a'},
        {"height",  required_argument, NULL, 'h'},
        {"weight",  required_argument, NULL, 'w'},
        {"gender",  required_argument, NULL, 'g'},
        {"add",     no_argument,       NULL,  3},
        {"print",   no_argument,       NULL,  2},
        {"help",    no_argument,       NULL,  1},
		{NULL, 0, NULL, 0}
	};

	int option;
	int option_index;

    while((option = getopt_long(argc, argv, 
                                short_options,
                                long_options, 
                                &option_index)) != -1)
    {

		switch(option){

			case 'n': // name
            {
				if (optarg)
                {
                    if(!flag_add) break;
                    
                    error_t err = validation_acl_string(p->name, optarg);
                    if(err != SUCCESS) return err;
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
                    if(!flag_add) break;
                    
                    error_t err = validation_acl_string(p->surname, optarg);
                    if(err != SUCCESS) return err;
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
                    if(!flag_add) break;

                    int i = 0; 
                    while(optarg[i] != '\0') 
                        if( optarg[i++] < '0' || optarg[i] > '9' )
                        { 
                            PRINT_ERROR("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
                            return PARSE_ACL_ERROR;
                        }
                    
                    int temp = atoi(optarg);
                    if(temp < 18 || temp > 125) 
                    {
                        PRINT_ERROR("Возраст от 18 до 125. Введено: %d\n", temp);
                        return PARSE_ACL_ERROR;
                    }

                    p->age = (uint8_t)temp;
                }
                else
                {
                    PRINT_ERROR("found size without value\n");
                    return NULL_PTR_ERROR;
                }
				break;
			};

            case 'h': // height
            {
                if(optarg)
                {
                    if(!flag_add) break;

                    int i = 0; 
                    while(optarg[i] != '\0') 
                        if( optarg[i++] < '0' || optarg[i] > '9' ) 
                        { 
                            PRINT_ERROR("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg);
                            return PARSE_ACL_ERROR;
                        }

                    int temp = atoi(optarg);
                    if(temp < 10 || temp > 500) 
                    {
                        PRINT_ERROR("Рост от 10 до 500. Введено: %d\n", temp);
                        return PARSE_ACL_ERROR;
                    }
                    
                    height = (uint16_t)temp;
                    
                }
                else
                {
                    PRINT_ERROR("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };

            case 'w': // weight
            {
                if(optarg)
                {
                    if(!flag_add) break;

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
                    if(!flag_add) break;

                    int i = 0; 

                        while(optarg[i] != '\0') 
                            if( optarg[i++] < '0' || optarg[i] > '9' ) 
                            {
                                PRINT_ERROR("Недопустимые символы. Ожидалось целое число. Аргумент %s\n", optarg); 
                                return PARSE_ACL_ERROR;
                            }

                        int temp = atoi(optarg);
                        if(temp < UNDEFINED || temp > FEMALE) 
                        {
                            PRINT_ERROR("Неверно указан пол. Мужской - 1, Женский - 2. Введено: %d\n", temp);
                            return PARSE_ACL_ERROR;
                        }
                        p->gender = (uint8_t)temp;
                }
                else
                {
                    PRINT_ERROR("found size without value\n");
                    return NULL_PTR_ERROR;
                }
                break;
            };
            
            // --help
            case 1: 
            {
				printf( "Можете запустить программу без аргументов и ввести данные вручную\n"
                        "Список доступных аргументов командной строки:\n"
                        "Допускается использование одной команды за запуск.\n"
                        "--print для печати данных из файла\n"
                        "--add для добавления новой записи. Далее опции разрешенные только при добавлении опции add\n"
                        "-n YourName или --name YourName , имя латиницей не более %"PRIu8" символов\n"
                        "-s YourSurname или --surname YourSurname , фамилия латинцей не более %"PRIu8" символов\n"
                        "-a 20 или --age 20 , ваш возраст, от 18 до 125 лет\n"
                        "-h 180 или --height 180 , ваш рост, целое число, от 10 до 500\n"
                        "-w 80 или --weight 80 , ваш вес, целое число, от 10 до 500\n"
                        "-g 1 или --gender 1 , ваш пол, целое число, Мужской - 1, Женский - 2\n"
                        , MAX_LEN - 2 , MAX_LEN - 2);
				exit(0);
			};

            // --add
            case 3: 
            {
                if(!flag_add)
                {
                    flag_add = 1;
                    optind = 0;
                }
                break;
            };

            // --print
            case 2: 
            {
                flag_print = 1;
                break;
            };

			case '?': default: {
                PRINT_ERROR("found unknown option or not found argument\n");
                return PARSE_ACL_ERROR;
                break;
			};
		};
	};

    error_t err = SUCCESS;

    if(flag_add)
    {
        // check parse args
        // name
        if(p->name[0] == '\0')
        {
            err = get_name(p->name, "Имя");

            if(err != SUCCESS)
                check_error(err);

        }

        // surname
        if(p->surname[0] == '\0')
        {
            err = get_name(p->surname, "Фамилия");

            if(err != SUCCESS)
                check_error(err);

        }

        // age
        if(p->age == 0) 
        {
            err = get_age(&p->age);
            
            if(err != SUCCESS)
                check_error(err);

        }

        // height
        if(height == 0) 
        {   
            err = get_height(&p->height);
            
            if(err != SUCCESS)
                check_error(err);

        }
        else p->height = height;
        
        // weight
        if(weight == 0) 
        {
            err = get_weight(&p->weight);
            
            if(err != SUCCESS)
                check_error(err);

        }
        else p->weight = weight;

        // gender
        if(p->gender == UNDEFINED || p->gender > FEMALE) 
        {
            err = get_gender(&p->gender);
            
            if(err != SUCCESS)
                check_error(err);

        }

        // save
        err = save_binary_data(p);
        if(err) check_error(err);
        printf("Запись добавлена\n");
    }
    

    // print
    if(flag_print)
    {
        person_t* per = NULL;
        err = SUCCESS;
        int count = 0;
        
        per = read_binary_data(&count, &err);

        if(!per && !err)
        { 
            printf("Файл пуст\n");
            return SUCCESS;
        }

        for(int i = 0; i < count; ++i)
        {
            printf("\nЗапись #%d:\n", i + 1);
            print_personal_data(&per[i]);
        }

        free(per);
    }

    return SUCCESS;
}



// print data struct person_t
error_t print_personal_data(const person_t * const p)
{
    if(!p)
    {
        PRINT_ERROR("Аргумент нулевой указатель\n");
        return NULL_PTR_ERROR;
    }

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

    return SUCCESS;
}

