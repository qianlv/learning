OBJECTS = fact_main.exe 6_10.exe find_char.exe 6_12.exe 6_22.exe \
		  init_list.exe 6_27.exe ref_return.exe overload.exe 6_54.exe \
		  6_55.exe

include ../GNU_makefile_template

fact.o : chapter6.h

fact_main.exe: fact.o fact_main.o
	$(CC) $(CCFLAGS) fact.o fact_main.o -o fact_main.exe
