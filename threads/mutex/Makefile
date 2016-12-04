CC = g++
CCFLAGS = -std=c++11 -Wall -g -O0 -pthread
LOCFLAGS =

object = test.exe producer_consumer.exe
all: $(object)

mutex.o: mutex.h
condition.o: condition.h
count_down_latch.h.o: count_down_latch.h
singleton.o: singleton.h
rw_lock.o: rw_lock.h
blockqueue.o: blockqueue.h
bounded_block_queue.o: bounded_block_queue.o

%.o: %.cpp
	$(CC) $(CCFLAGS) $(LOCFLAGS) -c $< -o $@

%.exe: %.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) $< -o $@

test.exe: mutex.o test.o condition.o count_down_latch.o singleton.o rw_lock.o blockqueue.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) test.o condition.o mutex.o count_down_latch.o rw_lock.o blockqueue.o \
		singleton.o -o test.exe

producer_consumer.exe: mutex.o producer_consumer.o condition.o blockqueue.o bounded_block_queue.o
	$(CC) $(CCFLAGS) $(LOCFLAGS) producer_consumer.o condition.o mutex.o blockqueue.o \
		bounded_block_queue.o -o producer_consumer.exe
clean:
	rm -rf *.o core *.stackdump *.exe
