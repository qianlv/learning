object = eprintf.o

list.out: eprintf.o list.c
	cc -o list.out eprintf.o list.c

all: $(object)
$(object): %.o: %.c

.PHONY: clean
clean:
	-rm *.o *.out

