#!/bin/sh

PROG=./decimal-format

num_tests=0
num_failures=0

function test_df()
{
	expected=$1
	shift
	result=`$PROG "$@"`
	ret=$?
	if [ "$ret" != "0" ]; then
		echo $PROG $@
		echo "had exit status $ret, not 0."
		let num_failures++
		return $ret
	fi
	if [ "$result" != "$expected" ]; then
		echo "$PROG $@ returned \"$result\", not \"$expected\"."
		let num_failures++
	fi
	let num_tests++
}

test_df "12,345.67" "##,##0.00" 12345.67
test_df "     0.40" "##,##0.00" 0.40
test_df "  -234.00" "##,##0.00" -234
test_df "-2,340.00" "##,##0.00" -2340
test_df "    12.3     " "#####0.0#####" 12.3
test_df "12.345   " "0.0#####" 12.345
test_df "00,012"    "00,000" 12
# Decimal point handling.
test_df "6"         "0" 6
test_df "6."        "0." 6
# Positive and negative zero.
test_df "0"         "" 0.0
test_df "-0"        "" -0.0
# Small group size.
test_df "1,2,3"     "#,#,#" 123
test_df "  123"     "#,#,," 123
# Rounding.
test_df "6"         "0" 5.5
test_df "10.00"     "0.00" 9.999
# Special cases.
test_df "nan" "" nan
test_df "inf" "" infinity
test_df "-inf" "" -infinity

if [ $num_failures -eq 0 ]; then
	echo "All $num_tests tests passed."
else
	echo "$num_failures/$num_tests failed."
fi
