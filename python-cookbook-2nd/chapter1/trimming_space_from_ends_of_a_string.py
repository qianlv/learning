#/usr/bin/python
#encoding=utf-8

x = '   hejxy  '
print '|',x.lstrip(),'|',x.rstrip(),'|',x.strip(),'|'

xx = 'xyyyx,xhej,xyy'
# 去除两边的'xy'
# '| ,xhej, |'
print '|',xx.strip('xy'),'|'
