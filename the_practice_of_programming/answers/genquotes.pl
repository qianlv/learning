#!/usr/bin/perl -w

# genquotes.pl: generate random CSV quotes like
# "LU",86.25,"11/4/1998","2:19PM",+4.0625,83.9375,86.875,83.625,5804800

$n = 10000;

sub gen_sym
{
	$len = int(rand() * 3) + 2;
	$sym = "";
	for (my $i = 0; $i < $len; $i++) {
		$sym .= chr(rand() * (ord('Z') - ord('A') + 1) + ord('A'));
	}

	return $sym;
}

sub gen_date
{
	my $month = int(rand() * 12) + 1;
	my $day = int(rand() * 28) + 1;
	my $year = int(rand() * 5) + 1998;

	return sprintf("%u/%u/%u", $month, $day, $year);
}

sub gen_time()
{
	my $hour = int(rand() * 12) + 1;
	my $minute = int(rand() * 60);
	if (rand() < 0.5) {
		$ampm = "AM";
	} else {
		$ampm = "PM";
	}

	return sprintf("%u:%02u%s", $hour, $minute, $ampm);
}

for ($i = 0; $i < $n; $i++) {
	printf("\"%s\",%.2f,\"%s\",\"%s\",%+.4f,%.4f,%.4f,%.4f,%u\n",
		gen_sym(), rand() * 100, gen_date(), gen_time(),
		rand() * 10 - 5, rand() * 100, rand() * 100, rand() * 100,
		rand() * 1000000);
}
