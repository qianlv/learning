#!/usr/bin/perl

while (<>) {
	# Use a negative look-behind assertion to avoid turning \r\n into \r\r\n.
	s/(?<!\r)\n/\r\n/g;
	print;
}
