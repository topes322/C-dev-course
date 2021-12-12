
objects = 	main.o errors.o file.o getters.o \
	 		mystring.o mystdlib.o validation_string.o

rel = 	@gcc -o release/test -O2 main.o errors.o file.o getters.o \
		mystring.o mystdlib.o validation_string.o

deb = 	gcc -o debug/test -g -O0 -Wall -Wextra \
		main.o errors.o file.o getters.o \
		mystring.o mystdlib.o validation_string.o


all: 	$(objects)
		$(rel)


debug: $(objects)
		$(deb)


release: $(objects)
		$(rel)


#tests
check:	all clean
#test1
		@cp test_files/person.bin.print1 person.bin
		@release/test --print > out1
		@rm person.bin
		@diff out1 test_files/print1
		@printf "Test 1 PASSED\n"
#test2
		@release/test --name Larry -s West -a 40 -h 200 --weight 100 -g 1 --add --print > out2
		@diff test_files/print2 out2
		@rm person.bin
		@printf "Test 2 PASSED\n"
#test3
		@release/test -s White -h 165 -g 2 --add --print < test_files/input3 > out3
		@diff test_files/print3 out3
		@rm person.bin
		@printf "Test 3 PASSED\n"

# object files
main.o: src/main.c includes/types.h includes/errors.h includes/file.h \
		includes/getters.h includes/mystdlib.h includes/mystring.h includes/validation_string.h
		@gcc -c src/main.c

errors.o: src/errors.c includes/errors.h
			@gcc -c src/errors.c

file.o: src/file.c includes/types.h includes/errors.h includes/file.h
		@gcc -c src/file.c

getters.o: src/getters.c includes/getters.h includes/types.h includes/errors.h
			@gcc -c src/getters.c

mystring.o: src/mystring.c includes/mystring.h
			@gcc -c src/mystring.c

mystdlib.o: src/mystdlib.c
			@gcc -c src/mystdlib.c

validation_string.o: src/validation_string.c includes/types.h includes/errors.h
						@gcc -c src/validation_string.c

#clean object files
clean:
	@rm -rf $(objects)