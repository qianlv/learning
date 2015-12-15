OBJECTS = 7_3.exe 7_7.exe 7_13.exe

include ../GNU_makefile_template

scales_data.o: scales_data.h
person.o: person.h

7_3.exe: scales_data.o 7_3.o
	 $(CC) $(CCFLAGS) scales_data.o 7_3.o -o 7_3.exe

7_7.exe: scales_data.o 7_7.o
	 $(CC) $(CCFLAGS) scales_data.o 7_7.o -o 7_7.exe

7_13.exe: scales_data.o 7_13.o
	 $(CC) $(CCFLAGS) scales_data.o 7_13.o -o 7_13.exe
