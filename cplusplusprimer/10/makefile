OBJECTS = 10_1.exe main.exe 10_3.exe 10_4.exe 10_13.exe 10_12.exe \
		  lambda.exe 10_17.exe 10_18_19.exe 10_20.exe 10_21.exe binding.exe \
		  other_iterator.exe 10_27.exe 10_28.exe 10_29.exe 10_30_31.exe

include ../GNU_makefile_template

LOCFLAGS = -I../7

10_12.exe: 10_12.o ../7/scales_data.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 10_12.o ../7/scales_data.o -o 10_12.exe

10_17.exe: 10_17.o ../7/scales_data.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 10_17.o ../7/scales_data.o -o 10_17.exe

generic_algorithm.o: generic_algorithm.h

main.exe: generic_algorithm.o main.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) main.o generic_algorithm.o -o main.exe

lambda.exe: generic_algorithm.o lambda.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) lambda.o generic_algorithm.o -o lambda.exe

10_18_19.exe: generic_algorithm.o 10_18_19.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 10_18_19.o generic_algorithm.o -o 10_18_19.exe

binding.exe: generic_algorithm.o binding.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) binding.o generic_algorithm.o -o binding.exe

