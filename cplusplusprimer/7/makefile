OBJECTS = 7_7.exe main.exe 7_27.exe 7_13.exe

include ../GNU_makefile_template

scales_data.o: scales_data.h
person.o: person.h
screen.o: screen.h
window.o: window.h
debug.o: debug.h

# 7_3.exe: scales_data.o 7_3.o
# 	 $(CC) $(CCFLAGS) scales_data.o 7_3.o -o 7_3.exe

7_7.exe: scales_data.o 7_7.o
	 $(CC) $(CCFLAGS) scales_data.o 7_7.o -o 7_7.exe

7_13.exe: scales_data.o 7_13.o
	 $(CC) $(CCFLAGS) scales_data.o 7_13.o -o 7_13.exe

main.exe: screen.o main.o window.o scales_data.o debug.o
	 $(CC) $(CCFLAGS) window.o screen.o main.o scales_data.o debug.o -o main.exe

7_27.exe: screen.o 7_27.o
	 $(CC) $(CCFLAGS) screen.o 7_27.o -o 7_27.exe

