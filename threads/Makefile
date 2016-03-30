CC = g++
CCFLAGS = -std=c++11 -Wall -g -O0 -pthread
LOCFLAGS =

object = simple_mutex.exe read_write_lock.exe condition_variables.exe \
		 barriers.exe recursive_mutex.exe thread_safe_function.exe \
		 thread_specific_data.exe
all: $(object)

thread_attr.o: thread_attr.h

%.o: %.cpp
	$(CC) $(CCFLAGS) $(LOCFLAGS) -c $< -o $@

%.exe: %.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) $< -o $@

recursive_mutex.exe: recursive_mutex.o thread_attr.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) recursive_mutex.o thread_attr.o -o recursive_mutex.exe -lrt


clean:
	rm -rf *.o core *.stackdump *.exe
