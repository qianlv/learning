CC = g++
CCFLAGS = -std=c++11 -Wall -g -O0 -pthread

object = simple_mutex.exe read_write_lock.exe
all: $(object)

#.PHONY: all

$(object): %.exe: %.cpp
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm -rf *.o core *.stackdump *.exe
