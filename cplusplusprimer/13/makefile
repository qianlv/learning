OBJECTS = 13_5.exe 13_8.exe destructor.exe 13_17_3.exe default.exe 13_28.exe \
		   13_31.exe folders.exe str_vec.exe String.exe main.exe 13_58.exe

include ../GNU_makefile_template

#LOCFLAGS = -I../7

hasptr.o: hasptr.h
scales_data.o: scales_data.h

13_5.exe: 13_5.o hasptr.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 13_5.o hasptr.o -o 13_5.exe

13_8.exe: hasptr.o 13_8.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 13_8.o hasptr.o -o 13_8.exe

destructor.exe: scales_data.o destructor.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) scales_data.o destructor.o -o destructor.exe

13_31.exe: hasptr.o 13_31.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 13_31.o hasptr.o -o 13_31.exe

main.exe: main.o hasptr.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) main.o hasptr.o -o main.exe


