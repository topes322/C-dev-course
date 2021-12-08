
objects = 	main.o errors.o file.o getters.o \
	 		mystring.o mystdlib.o validation_string.o

rel = 	gcc -o release/test -O2 main.o errors.o file.o getters.o \
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



# object files
main.o: src/main.c includes/types.h includes/errors.h includes/file.h \
		includes/getters.h includes/mystdlib.h includes/mystring.h includes/validation_string.h
		gcc -c src/main.c

errors.o: src/errors.c includes/errors.h
			gcc -c src/errors.c

file.o: src/file.c includes/types.h includes/errors.h includes/file.h
		gcc -c src/file.c

getters.o: src/getters.c includes/getters.h includes/types.h includes/errors.h
			gcc -c src/getters.c

mystring.o: src/mystring.c includes/mystring.h
			gcc -c src/mystring.c

mystdlib.o: src/mystdlib.c
			gcc -c src/mystdlib.c

validation_string.o: src/validation_string.c includes/types.h includes/errors.h
						gcc -c src/validation_string.c

#clean object files
clean:
	rm $(objects)