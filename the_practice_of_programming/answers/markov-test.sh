#!/bin/sh

TEXTS="2ws2410.txt 76.txt kjv10.txt ulyss12.txt"

for text in $TEXTS; do
	echo "$text:"
	echo "markov"
	time ./markov < $text > markov-$text
	tail -n 1 markov-$text
	rm -f markov-$text
	echo "markov-hash"
	time ./markov-hash < $text > markov-hash-$text
	tail -n 1 markov-hash-$text
	rm -f markov-hash-$text
done
