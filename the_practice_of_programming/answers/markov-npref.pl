# Copyright (C) 1999 Lucent Technologies
# Excerpted from 'The Practice of Programming'
# by Brian W. Kernighan and Rob Pike
# Modified by David Fifield for exercise 3-7

# markov.pl: markov chain algorithm

$MAXGEN = 10000;
$NONWORD = "\n";
$NPREF = 2;
@w = ($NONWORD) x $NPREF;
while (<>) {                    # read each line of input
	foreach (split) {
		push(@{$statetab{join $NONWORD, @w}}, $_);
		shift @w;
		push @w, $_;
	}
}
push(@{$statetab{@w}}, $NONWORD); 	# add tail

@w = ($NONWORD) x $NPREF;
for ($i = 0; $i < $MAXGEN; $i++) {
	$suf = $statetab{join $NONWORD, @w};	# array reference
	$r = int(rand @$suf);		# @$suf is number of elems
	exit if (($t = $suf->[$r]) eq $NONWORD);
	print "$t\n";
	shift @w;
	push @w, $t;
}
