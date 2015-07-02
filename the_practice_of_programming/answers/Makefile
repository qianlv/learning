PROGRAMS = ex1-6 qsort-iter QuicksortTest qsort-race slow-sort growarray \
	nvlist list-test-c list-test-c++ ListTestJava tree treesort hash \
	hash-grow hash-point randselect word-savings markov markov-hash \
	markov-nosentinel Markov $(MARKOV++_VARIATIONS) markov++-simple \
	csvgetline1 csvgetline2 $(CSV_SPLIT_TESTS) csvgetline2-a \
	csvgetline2-b csvgetline2-c csvgetline2-init csvw csvgetlinec++ \
	Csv csvgetlinec++-iter csvgetline2-new malloc-mistakes strings \
	vis ex6-1 test-ctime freq printf-test mem-test spam-1 spam-2 \
	timer-test memset smalloc op-cost op-cost-c++ OpCost conditional \
	pack-test pack-c++.o printf decimal-format DecimalFormat grep \
	match-test gres utf8cat rematch quine

# Variations on the C++ Markov program. Command-line define directives override
# the types used by the program.
MARKOV++_VARIATIONS = \
	$(foreach queue,deque list vector array, \
		$(foreach list,list vector, \
			markov++-$(queue)-$(list)))

CSV_SPLIT_TESTS = csv-split-test-0 csv-split-test-1 csv-split-test-2 csv-split-test-3

CFLAGS = -g -Wall
CXXFLAGS = $(CFLAGS)

all: $(PROGRAMS)

%: %.java
	gcj $^ --main=$* -o $@

ex1-6: CFLAGS += -Wno-sequence-point

slow-sort: CFLAGS += -Wno-unused

nvlist: nvlist.o eprintf.o

list-test-c: list-test-c.o list-generic-c.o
list-test-c.o: list-test-c.c list-generic-c.h

list-test-c++: list-test-c++.o
	$(CXX) $(LDFLAGS) $^ -o $@
list-test-c++.o: list-test-c++.cpp list-generic-c++.h

ListTestJava: ListTestJava.java List.java

tree: tree.o eprintf.o

treesort: treesort.o eprintf.o

hash: hash.o eprintf.o

hash-grow: hash-grow.o eprintf.o

hash-point: LDLIBS += -lm

word-savings: word-savings.o eprintf.o

markov: markov.o eprintf.o
markov: CFLAGS += -Wno-unused -Wno-format

markov-hash: markov-hash.o eprintf.o
markov-hash: CFLAGS += -Wno-unused -Wno-format

markov-nosentinel: markov-nosentinel.o eprintf.o
markov-nosentinel: CFLAGS += -Wno-unused -Wno-format

markov++: CXXFLAGS += -Wno-sign-compare

# This builds the markov++ variations like markov++-deque-vector
$(MARKOV++_VARIATIONS): CXXFLAGS += -Wno-sign-compare
$(MARKOV++_VARIATIONS): markov++.c
# Change a string like "markov++-deque-vector"
# into "-DQUEUE_TYPE_DEQUE -DLIST_TYPE_VECTOR".
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ \
		$(join -DQUEUE_TYPE_ -DLIST_TYPE_,\
		$(shell echo $@ | sed -e "s/^markov++-//" | tr a-z- "A-Z "))

markov++-simple: markov++-simple.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

csvgetline2%.o: csvgetline2%.c csv.h

csvgetline2-c: csvgetline2-c.o charclass.o eprintf.o match.o utf8.o

csv-split-%.o: csv-split-%.c csv.h

csv-split-test-%: csv-split-%.o csv-split-test.o
	$(CC) $(LDFLAGS) -o $@ $^

csvgetlinec++ csvgetlinec++-iter: CXXFLAGS += -Wno-sign-compare
csvgetlinec++: csvgetlinec++.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
csvgetlinec++-iter: csvgetlinec++-iter.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

malloc-mistakes: malloc-mistakes.o safe-malloc.o

strings: strings.o eprintf.o

vis: vis.o eprintf.o

ex6-1: CXXFLAGS += -Wno-write-strings

freq: freq.o eprintf.o

printf-test: printf-test.o eprintf.o

spam-1: CFLAGS += -Wno-sign-compare
spam-1: spam-1.o eprintf.o

spam-2: CFLAGS += -Wno-sign-compare
spam-2: spam-2.o eprintf.o

timer-test: timer-test.o timer.o

memset: memset.o timer.o

op-cost: LDLIBS += -lm

OpCost.java: OpCost.java.in
	cpp -P $< -o $@

pack-test: pack-test.o pack.o eprintf.o

pack-c++.o: CXXFLAGS += -Wno-write-strings

printf: printf.o eprintf.o

# decimal-format.c uses the signbit and isfinite functions, only in C99.
decimal-format: CFLAGS += -std=c99
decimal-format: LDLIBS += -lm
decimal-format: decimal-format.o eprintf.o

grep: grep.o charclass.o eprintf.o match.o utf8.o

match-test: match-test.o timer.o

gres: gres.o charclass.o eprintf.o match.o utf8.o

utf8cat: utf8cat.o eprintf.o utf8.o

rematch: rematch.o charclass.o eprintf.o match.o utf8.o

clean:
	rm -f *.o *.class $(PROGRAMS)

.PHONY: all clean
