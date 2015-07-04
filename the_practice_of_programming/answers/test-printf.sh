#!/bin/sh

PRINTF=./printf

num_tests=0
num_failures=0

function test_printf()
{
	expected=$1
	shift
	result=`$PRINTF "$@"`
	ret=$?
	if [ "$result" != "$expected" ]; then
		echo $PRINTF $@
		echo "returned \"$result\", not \"$expected\"."
		let num_failures++
	elif [ "$ret" != "0" ]; then
		echo $PRINTF $@
		echo "had exit status $ret, not 0."
		let num_failures++
	fi
	let num_tests++
}

function test_printf_error()
{
	if $PRINTF "$@" > /dev/null 2>&1; then
		echo $PRINTF $@
		echo "did not signal error."
		let num_failures++
	fi
	let num_tests++
}

test_printf "" ""
test_printf "abc" "abc"
test_printf "%" "%%"
test_printf "a\nb\nc" "a\nb\nc"
test_printf "abc" "%s" "abc"
test_printf "       abc" "%10s" "abc"
test_printf "abc       " "%-10s" "abc"
test_printf "       abc" "%*s" 10 "abc"
test_printf "a" "%c" 97
test_printf "25" "%d" 25
test_printf "-25" "%d" -25
test_printf "25" "%i" 25
test_printf "250000000" "%ld" 250000000
test_printf "-1234" "%hd" -1234
test_printf "55" "%o" 45
test_printf "55" "%o" 055
test_printf "25" "%u" 25
test_printf "2d" "%x" 45
test_printf "2d" "%x" 0x2D
test_printf "2D" "%X" 45
test_printf "25.00" "%.2f" 25
test_printf "25.00" "%.2Lf" 25
test_printf "2.6e+02" "%.1e" 264
test_printf "2.64e+02" "%.2e" 264
test_printf "2.6E+02" "%.1E" 264
test_printf "2.64E+02" "%.2E" 264
test_printf "25" "%.2g" 25
test_printf "2.6e+02" "%.2g" 264
test_printf "25" "%.2G" 25
test_printf "2.6E+02" "%.2G" 264
test_printf " 3.450000" "%*f" 9 3.45
test_printf " 3.450000" "%*.f" 9 3.45
test_printf "3.4500" "%.*f" 4 3.45
test_printf "   3.4500" "%*.*f" 9 4 3.45

# These tests should produce a non-zero exit code.
test_printf_error "" "%s"
test_printf_error "%d" abc
test_printf_error "%*.*.*f" 1.3
test_printf_error "%q" 1.3
test_printf_error "%d"
test_printf_error "%*d" 5
test_printf_error "%.*d" 5
test_printf_error "%*.*d" 5 5
test_printf_error "%n" 5 5
test_printf_error "%p" 0x12345678
test_printf_error "%d" 1 2 3
test_printf_error "%*.*d" 1 2 3 4

if [ $num_failures -eq 0 ]; then
	echo "All $num_tests tests passed."
else
	echo "$num_failures/$num_tests failed."
fi
