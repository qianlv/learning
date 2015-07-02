#!/usr/bin/env python

# markov.py: markov chain algorithm

import sys
import random

MAXGEN = 10000
NONWORD = "\n"
NPREF = 2

statetab = {}
w = [NONWORD] * NPREF
for line in sys.stdin:
	for word in line.split():
		# append to suffix list
		statetab.setdefault(tuple(w), []).append(word)
		# advance state
		w.append(word)
		w.pop(0)
statetab.setdefault(tuple(w), []).append(NONWORD)

w = [NONWORD] * NPREF
i = 0
while i < MAXGEN:
	suffixes = statetab[tuple(w)]
	word = suffixes[random.randrange(0, len(suffixes))]
	if word == NONWORD:
		break
	print word
	w.append(word)
	w.pop(0)
	i += 1
