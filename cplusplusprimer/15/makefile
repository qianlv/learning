ver = NODEBUG
OBJECTS = 15_6.exe 15_26.exe main.exe text_query.exe

include ../GNU_makefile_template
ifeq ($(ver), DEBUG)
LOCFLAGS = -D$(ver)
endif

book.o: book.h
basket.o: basket.h

15_6.exe: 15_6.o book.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 15_6.o book.o -o 15_6.exe

15_26.exe: 15_26.o book.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) 15_26.o book.o -o 15_26.exe

main.exe: main.o book.o basket.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) main.o book.o basket.o -o main.exe

