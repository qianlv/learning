OBJECTS = 14_2.exe 14_5.exe 14_16.exe main.exe 14_32.exe print_string.exe \
		  14_35.exe 14_42.exe 14_43.exe function.exe smallint.exe

include ../GNU_makefile_template
#LOCFLAGS = -I../7

scales_data.o: scales_data.h
employee.o: employee.h
blob.o: blob.h
blobptr.o: blobptr.h
str_vec.o: str_vec.h
String.o: String.h

14_2.exe: 14_2.o scales_data.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 14_2.o scales_data.o -o 14_2.exe

14_5.exe: 14_5.o employee.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 14_5.o employee.o -o 14_5.exe

14_16.exe: 14_16.o blob.o blobptr.o str_vec.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 14_16.o blob.o blobptr.o str_vec.o -o 14_16.exe

main.exe: main.o blob.o blobptr.o str_vec.o String.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) main.o blob.o blobptr.o str_vec.o String.o -o main.exe

14_32.exe: 14_32.o blob.o blobptr.o 
	$(CC) $(CCFLAGS) $(LOCFLAGS) 14_32.o blob.o blobptr.o -o 14_32.exe


