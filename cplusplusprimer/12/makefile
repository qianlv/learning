OBJECTS = 12_6_7.exe 12_20.exe 12_23.exe allocater.exe 12_30.exe 12_32.exe

include ../GNU_makefile_template

#LOCFLAGS = -I../7

blob.o : blob.h 
blobptr.o: blobptr.h 
text_query.o: text_query.h
text_query_strblob.o: text_query_strblob.h

12_20.exe: 12_20.o blob.o blobptr.o
	$(CC) $(LOCFLAGS) 12_20.o blob.o blobptr.o -o 12_20.exe

12_30.exe: 12_30.o text_query.o
	$(CC) $(LOCFLAGS) 12_30.o text_query.o -o 12_30.exe

12_32.exe: 12_32.o text_query_strblob.o blob.o blobptr.o
	$(CC) $(LOCFLAGS) 12_32.o text_query_strblob.o blob.o blobptr.o -o 12_32.exe
