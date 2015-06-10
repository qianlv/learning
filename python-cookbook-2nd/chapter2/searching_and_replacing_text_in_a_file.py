#!/usr/bin/python
#encoding=utf-8

import os, sys
nargs = len(sys.argv)

if nargs < 3 or nargs > 5:
    print "usage: %s search_text replace_text [infile [outfile]]" % \
           os.path.basename(sys.argv[0])
else:
    stext = sys.argv[1]
    rtext = sys.argv[2]
    input_file = sys.stdin
    output_file = sys.stdout
    if nargs > 3:
        input_file = open(sys.argv[3])
    if nargs > 4:
        output_file = opne(sys.argv[4], 'w')
    for s in input_file:
        output_file.write(s.replace(stext, rtext))
    # 内存充足的话
    # output_file.write(input_file.read().replace(stext, rtext))
    output_file.close()
    input_file.close()
