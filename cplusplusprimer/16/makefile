ver = NODEBUG
OBJECTS = main.exe

include ../GNU_makefile_template
ifeq ($(ver), DEBUG)
LOCFLAGS = -D$(ver)
endif

blob.o: blob.h
vec.o: vec.h
genic_function.o: genic_function.h

main.exe: main.o genic_function.o blob.o vec.o 
	$(CC) $(CCFLAGS) $(LOCFLAGS) main.o genic_function.o blob.o vec.o -o main.exe

