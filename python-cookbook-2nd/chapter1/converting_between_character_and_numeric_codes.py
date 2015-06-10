#/usr/bin/python
#encoding=utf-8

#字符与字符值之间转换


print ord('a') #接受一个ascii或一个长度为1的Unicode字符串当作参数,返回对应的值
# Return a string of one character whose ASCII code is the integer i,
# The argument must be in the range [0..255],
# ValueError will be raised if i is outside that range.
print chr(97)

print ord(u'\u2020')
#return the Unicode string of one character whose Unicode code is the integer i
print repr(unichr(8224))

print map(ord, "abc")
print ''.join(map(chr, range(97, 100)))


