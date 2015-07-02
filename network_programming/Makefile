target = client.out server.out listener.out selectserver.out \
		 talker.out showip.out
object = client.o server.o listener.o selectserver.o \
		 talker.o showip.o

result: $(target)
$(target): %.out: %.o
	cc $< -o $@
all: $(object)
$(object): %.o: %.c
	cc -c $< -o $@

.PHONY: clean
clean:
	-rm *.o *.out


