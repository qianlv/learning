OBJECTS = 8_1_2.exe io.exe fio.exe 8_4.exe 8_5.exe stringio.exe 8_9.exe \
		  8_10.exe 8_11.exe

include ../GNU_makefile_template

LOCFLAGS = -I../7

fio.exe: fio.o ../7/scales_data.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) fio.o ../7/scales_data.o -o fio.exe


