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


error_t input_name(char*, char*);


int8_t validation_acl_string(char *, char *);



int main(int argc, char* argv[])
{
    person_t person = {{'\0'}, {'\0'}, 0 , 0 , 0, UNDEFINED };


    //__CHAR16_TYPE__ q = L'a';
    //printf("%u\n", q);

    if(argc > 1)
    {
        /*
        for (uint8_t i = 0; i < argc; i++)
        {
            printf("argc #%u: %s\n", i, argv[i]);
        }*/
        error_t err = parse_command_line_arg(&person, argc, argv);
        if(err != SUCSESS) check_error(err);
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
    return 0;
}



// user enter data into struct person_t
error_t get_personal_data(person_t* data)
{
    if(!data) return NULL_PTR_ERROR;
    error_t err = SUCSESS;


    err = input_name(data->name, "Имя");
    if(err != 0) return err;

    err = input_name(data->surname, "Фамилия");
    if(err != 0) return err;

    //
    
    do
    {
        printf("Возраст(целое число от 18 до 125): ");
        if(scanf("%"PRIu8, &data->age) != 1) return PARSE_ERROR;

        if(data->age < 18 || data->age > 125)
            printf("\nВведен некорректный возраст. Вы ввели %"PRIu8"\nНеобходимо ввести возраст от 18 до 125 лет\nПопробуйте снова\n", data->age);

    } while (data->age < 18 || data->age > 125);
    
    //
    do
    {
        printf("Рост см(целое число от 10 до 500): ");
        if(scanf("%"PRIu16, &data->height) != 1) return PARSE_ERROR;

        if(data->height < 10 || data->height > 500)
            printf("\nВведен некорректный рост. Вы ввели %"PRIu8"\nНеобходимо ввести рост от 10 до 500\nПопробуйте снова\n", data->height);

    } while(data->height < 10 || data->height > 500);

    //

    do
    {
        printf("Вес кг(целое число от 10 до 500): ");
        if(scanf("%"PRIu16, &data->weight) != 1) return PARSE_ERROR;

        if(data->weight < 10 || data->weight > 500)
                printf("\nВведен некорректный вес. Вы ввели %"PRIu8"\nНеобходимо ввести вес от 10 до 500\nПопробуйте снова\n", data->weight);

    } while(data->weight < 10 || data->weight > 500);

    //
    
    do
    {   
        printf("Выберите ваш пол(Мужской - 1, Женский - 2): ");
        data->gender = UNDEFINED;
        if(scanf("%"PRIu8, &data->gender) != 1) return PARSE_ERROR;
        if(data->gender > FEMALE)
            printf("\nНекорректно введены данные. Попробуйте снова.\nМужской - 1, Женский - 2\nВы ввели: %u\n", data->gender);
    } while(data->gender > FEMALE);

    return SUCSESS;
}



// parse command line arguments
// prompt for user input if there is not enough data
error_t parse_command_line_arg(person_t* p, int argc, char* argv[])
{

    const char* short_options = "n:s:a:h:w:g";
    
	const struct option long_options[] = {
		{"name", required_argument, NULL, 'n'},
		{"surname", required_argument, NULL, 's'},
		{"age", required_argument, NULL, 'a'},
        {"height", required_argument, NULL, 'h'},
        {"weight", required_argument, NULL, 'w'},
        {"gender", required_argument, NULL, 'g'},
        //{"help", no_argument, NULL, 1},
		{NULL, 0, NULL, 0}
	};

	int rez;
	int option_index;

    //https://firststeps.ru/linux/r.php?11
    while ((rez = getopt_long(  argc, argv, 
                                short_options,
		                        long_options, 
                                &option_index)) != -1)
    {

        //printf("rez = %d\noption_index = %d\n", rez, option_index);

		switch(rez){
			case 'n': // name
            {
                printf("\n-n\n");
				if (optarg != NULL)
                {
                    validation_acl_string(p->name, optarg);
                    printf("p->name = %s\n", p->name);
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
                printf("\n-s\n");
				if (optarg != NULL)
                {
                    validation_acl_string(p->surname, optarg);
                    printf("p->surname = %s\n", p->surname);
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
                printf("-a\n");
                if (optarg != NULL)
                {
                    int i = 0; 
                    uint8_t flag = 0;
                    while(optarg[i++] != '\0') 
                        if(optarg[i] < '0' && optarg[i] < '9') 
                        { 
                            printf("Недопустимые символы\n");
                            flag++;
                            break;
                        }

                    if(flag) break;

                    p->age = (uint8_t)atoi(optarg);
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
                break;
            };

            case 'w': // weight
            {
                break;
            };

            case 'g': // gender
            {
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
				printf("found unknown option\n");
                return PARSE_ACL_ERROR;
                break;
			};
		};
	};

    // check parse args
    if(p->name[0] = '\0');
    if(p->surname[0] = '\0');
    if(p->age = 0);
    if(p->height = 0);
    if(p->weight = 0);
    if(p->gender = UNDEFINED);

    return SUCSESS;
}


int8_t validation_acl_string(char * name, char * optarg)
{

    printf("%s\n", optarg);
    printf("strlen(optarg) = %d\nMAX_LEN = %u\n", strlen(optarg), MAX_LEN - 2);

    uint8_t flag = 0;
    if(strlen(optarg) > MAX_LEN - 2) flag++;

    uint8_t i = 0;
    while(optarg[i] != '\0')
    {
        if(!(optarg[i] >= 'a' && optarg[i] <= 'z') 
        && !(optarg[i] >= 'A' && optarg[i] <= 'Z'))
        {
            flag++;
            printf("В качестве аргумента использованы недопустимые символы.\n");
            break;
        }
        i++;
    }

    if(flag == 0) strcpy(name, optarg);
        
    return flag;
}

error_t input_name(char* name, char* n)
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
            /*
            printf("%c - %d\n", data->second_name[i], data->second_name[i]);
            printf("%c - %d\n", 'a','a' );
            printf("%c - %d\n", 'z','z');
            printf("%c - %d\n", 'A','A');
            printf("%c - %d\n", 'Z','Z');
            printf("%d\n", data->second_name[i] < 'a' || data->second_name[i] > 'z' &
               data->second_name[i] < 'A' || data->second_name[i] > 'Z');*/

            if(!(name[i] >= 'a' && name[i] <= 'z') 
            && !(name[i] >= 'A' && name[i] <= 'Z')
            //&& !(data->second_name[i] >= 'а' && data->second_name[i] <= 'я')
            //&& !(data->second_name[i] >= 'А' && data->second_name[i] <= 'Я')
            // а = 45264 - 2 bytes
            // А = 37072 
            // я = 36817 
            )
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
}



error_t validation_string(char * str)
{
    if(!str) return NULL_PTR_ERROR;

    if(scanf("%11s", str) != 1) return PARSE_ERROR;
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