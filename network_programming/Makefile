target = client.out server.out listener.out selectserver.out \
		 talker.out showip.out mmap.out logical_to_physical_block.out \
		 sys_log.out simple_signal.out another_simple_signal.out

result: $(target) epoll.out
$(target): %.out: %.c
	cc -Wall $< -o $@
epoll.out: epoll.c base_socket.o
	cc -g -Wall -o epoll.out epoll.c base_socket.o

base_socket.o: base_socket.c

.PHONY: clean
clean:
	-rm *.o *.out


