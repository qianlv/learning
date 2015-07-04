#!/usr/bin/perl

while (<>) {
	s/\r\n/\n/g;
	print;
}
