object = csapp.o
tiny: csapp.o tiny.c
	cc -pthread -o tiny csapp.o tiny.c
csapp.o: csapp.h

.PHONY: clean
clean:
	-rm *.o tiny
