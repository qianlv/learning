# Copyright (C) 1999 Lucent Technologies
# Excerpted from 'The Practice of Programming'
# by Brian W. Kernighan and Rob Pike
# Modified by David Fifield for exercise 3-7

function join(array) {
	result = array[1];
	for (x = 2; x <= NPREF; x++)
		result = result SUBSEP array[x];
	return result;
}

# markov.awk: markov chain algorithm
BEGIN {	MAXGEN = 10000; NPREF = 2; NONWORD = "\n";
	for (i = 1; i <= NPREF; i++) {
		w[i] = NONWORD;
	}
}

{	for (i = 1; i <= NF; i++) { 	# read all words
		statetab[join(w),++nsuffix[join(w)]] = $i
		for (j = 1; j <= NPREF - 1; j++) {
			w[j] = w[j + 1];
		}
		w[NPREF] = $i;
	}
}

END {
	statetab[join(w),++nsuffix[join(w)]] = NONWORD	# add tail
	for (i = 1; i <= NPREF; i++) {
		w[i] = NONWORD;
	}
	for (i = 0; i < MAXGEN; i++) {	# generate
		r = int(rand()*nsuffix[join(w)]) + 1  # nsuffix >= 1
		p = statetab[join(w),r]
		if (p == NONWORD)
			exit
		print p
		# advance chain
		for (j = 1; j <= NPREF - 1; j++) {
			w[j] = w[j + 1];
		}
		w[NPREF] = p;
	}
}	
