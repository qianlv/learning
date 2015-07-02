#!/usr/bin/env python

import re
import sys

if len(sys.argv) != 3:
	print >> sys.stderr, "usage: %s <re> <str>"
	sys.exit(1)

try:
	m = re.search(sys.argv[1].decode("UTF-8"), sys.argv[2].decode("UTF-8"), flags = re.S)
except:
	sys.exit(2)

if m is not None:
	sys.exit(0)
else:
	sys.exit(1)
