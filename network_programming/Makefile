target = client.out server.out listener.out selectserver.out \
		 talker.out showip.out

result: $(target) epoll.out
$(target): %.out: %.c
	cc $< -o $@
epoll.out: epoll.c base_socket.o
	cc -g -Wall -o epoll.out epoll.c base_socket.o

base_socket.o: base_socket.c

.PHONY: clean
clean:
	-rm *.o *.out


