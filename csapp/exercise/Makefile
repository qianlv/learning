object2 = csapp.o 11-2.o
object3 = csapp.o 11-3.o
object5 = csapp.o 11-5.o
object6 = csapp.o 11-6.o
object7 = csapp.o 11-7.o
object10 = csapp.o 11-10.o

exercise: exercise2 exercise3 exercise5 exercise6 \
		  exercise7 exercise10
.PHONY: exercise

exercise2: $(object2)
	cc -pthread -o exercise2.out $(object2)
exercise3: $(object3)
	cc -pthread -o exercise3.out $(object3)
exercise5: $(object5)
	cc -pthread -o exercise5.out $(object5)
exercise6: $(object6)
	cc -pthread -o exercise6.out $(object6)
exercise7: $(object7)
	cc -pthread -o exercise7.out $(object7)
exercise10: $(object10)
	cc -pthread -o exercise10.out $(object10)

csapp.o: csapp.h
object = 11-2.o 11-3.o 11-5.o 11-6.o 11-7.o 11-10.o
all: $(object)
$(object): %.o: %.c
	cc -c $< -o $@

.PHONY: clean
clean:
	-rm *.o
	-rm *.ouout

