#!/usr/bin/env python

# Automated regular expression tester.
# Usage:
# 	./re-test.py <prog> [<prog> ...]
# Each argument passed to this program is the name of a program that
# tests a single string against a single regular expression. Many
# regular expressions are generated and passed to the programs given. A
# line is printed whenever a string unexpectedly matches or doesn't
# match.
#
# Each program must take arguments in the form
# 	<re> <string>
# Each program must return 0 for a match, 1 for no match, and 2 for any
# kind of error.

import re
import subprocess
import sys

PROG = None

MATCH, NOMATCH, ERROR = "MATCH", "NOMATCH", "ERROR"

def run_matchprog(prog, regex, s):
	code = subprocess.call([prog, regex.encode("UTF-8"), s.encode("UTF-8")],
		stderr = subprocess.PIPE)
	if code == 0:
		return MATCH
	elif code == 1:
		return NOMATCH
	else:
		return ERROR
	return code == 0

def re_match(regex, s):
	return run_matchprog(PROG, regex, s)

def re_expect(regex, s, expected):
	result = re_match(regex, s)
	line = "match(" + repr(regex) + ", " + repr(s) + "): "
	if result != expected:
		print line + "expected " + expected + ", got " + result + "."
	else:
		pass

def esc(s):
	def backslash(m):
		return u"\\" + m.group()

	return re.sub(u'[][|^$()*?+.\\\\-]', backslash, s)

def legal(i):
	return not (i >= 0xD800 and i <= 0xDFFF) and i != 0xFFFE and i != 0xFFFF

def re_test(prog):
	global PROG

	PROG = prog

	re_expect('', '', MATCH)
	re_expect('', 'a', MATCH)
	re_expect('', u'\uFFFF', MATCH)

	for i in range(5):
		for j in range(5):
			re_expect(u'\N{SNOWMAN}', ('x' * i) + u'\N{SNOWMAN}' + ('y' * j), MATCH)

	for i in range(1, 5):
		for j in range(5):
			re_expect(('a' * i) + '*', ('a' * j), i - 1 <= j and MATCH or NOMATCH)
			re_expect(('a' * i) + '+', ('a' * j), i - 1 < j and MATCH or NOMATCH)
			re_expect(('a' * i) + '?', ('a' * j), i - 1 <= j and MATCH or NOMATCH)
			re_expect('^' + ('a' * i) + '?$', ('a' * j), i - 1 <= j <= i and MATCH or NOMATCH)

	for i in range(5):
		re_expect('^house', ('x' * i) + 'house', i == 0 and MATCH or NOMATCH)
		re_expect('house$', 'house' + ('x' * i), i == 0 and MATCH or NOMATCH)
		re_expect('^house$', ('x' * i) + 'house', i == 0 and MATCH or NOMATCH)
		re_expect('^house$', 'house' + ('x' * i), i == 0 and MATCH or NOMATCH)

	for i in range(5):
		re_expect(u'^.*$', unichr(i + 1) * i, MATCH)

	re_expect('^^', '', MATCH)
	re_expect('^^', 'a', MATCH)
	re_expect('^a', 'a', MATCH)
	re_expect('^a', 'aa', MATCH)
	re_expect('^a$', 'a', MATCH)
	re_expect('a$', 'a', MATCH)
	re_expect('a$', 'aa', MATCH)
	re_expect('$$', '', MATCH)
	re_expect('$$', 'a', MATCH)

	def chr_iter():
		for i in range(1, 0x100):
			yield i
		for i in range(0x100, 0x10000, 0x101):
			yield i
		yield 0xD7FF
		yield 0xD800
		yield 0xDFFF
		yield 0xE000
		yield 0xFFFE
		yield 0xFFFF

	for i in chr_iter():
		re_expect(u'.', esc(unichr(i)), legal(i) and MATCH or NOMATCH)
		re_expect(u'[\u0001-\uFFFD]', esc(unichr(i)), legal(i) and MATCH or NOMATCH)

	for i in chr_iter():
		regex = esc(unichr(i))
		if i > 1:
			re_expect(regex, unichr(i - 1), legal(i) and NOMATCH or ERROR)
		re_expect(regex, unichr(i), legal(i) and MATCH or ERROR)
		if i < 0xFFFF:
			re_expect(regex, unichr(i + 1), legal(i) and NOMATCH or ERROR)

	for i in chr_iter():
		regex = '[' + esc(unichr(i)) + ']'
		if i > 1:
			re_expect(regex, unichr(i - 1), legal(i) and NOMATCH or ERROR)
		re_expect(regex, unichr(i), legal(i) and MATCH or ERROR)
		if i < 0xFFFF:
			re_expect(regex, unichr(i + 1), legal(i) and NOMATCH or ERROR)
		re_expect('[' + esc(unichr(max(1, i - 10))) + '-' + esc(unichr(min(0xFFFF, i + 10))) + ']', unichr(i), (legal(max(1, i - 10)) and legal(min(0xFFFF, i + 10)) and MATCH) or ERROR)

	for i in chr_iter():
		regex = '[^' + esc(unichr(i)) + ']'
		if i > 1:
			expected = MATCH
			if not legal(i):
				expected = ERROR
			elif not legal(i - 1):
				expected = NOMATCH
			re_expect(regex, unichr(i - 1), expected)
		re_expect(regex, unichr(i), legal(i) and NOMATCH or ERROR)
		if i < 0xFFFF:
			expected = MATCH
			if not legal(i):
				expected = ERROR
			elif not legal(i + 1):
				expected = NOMATCH
			re_expect(regex, unichr(i + 1), expected)
		expected = NOMATCH
		if not legal(i):
			expected = ERROR
		elif not legal(max(1, i + 10)) or not legal(min(0xFFFF, i + 10)):
			expected = NOMATCH
		re_expect('[^' + esc(unichr(max(1, i - 10))) + '-' + esc(unichr(min(0xFFFF, i + 10))) + ']', unichr(i), (legal(max(1, i - 10)) and legal(min(0xFFFF, i + 10)) and NOMATCH) or ERROR)

	re_expect('[-abcdef]', '-', MATCH)
	re_expect('[abc-def]', '-', NOMATCH)
	re_expect('[abcdef-]', '-', MATCH)
	re_expect('[^-a]', '-', NOMATCH)

	re_expect('[]]', ']', MATCH)
	re_expect('[]ab]', ']', MATCH)
	re_expect('[]a]', 'a', MATCH)
	re_expect('[]a]', '[', NOMATCH)
	re_expect('[[]', '[', MATCH)
	re_expect('[[]a]', '[a]', MATCH)
	re_expect('[\\]]', '\\', NOMATCH)
	re_expect('[\\]]', ']', MATCH)
	re_expect('[\\\\]', '\\', MATCH)

	re_expect('[^]]', ']', NOMATCH)
	re_expect('[^]a]', 'a', NOMATCH)
	re_expect('[^^]', '^', NOMATCH)
	re_expect('[^\\]]', '\\', MATCH)
	re_expect('[^\\]]', ']', NOMATCH)

	re_expect('^[abc]*$', '', MATCH)
	re_expect('^[abc]*$', 'a', MATCH)
	re_expect('^[abc]*$', 'aa', MATCH)
	re_expect('^[abc]*$', 'ab', MATCH)
	re_expect('^[abc]*$', 'abc', MATCH)
	re_expect('^[abc]*$', 'abcd', NOMATCH)
	re_expect('^[abc]*$', 'd', NOMATCH)

for prog in sys.argv[1:]:
	print "Now testing %s." % prog
	re_test(prog)
