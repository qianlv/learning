#!/usr/bin/python
#encoding=utf-8

# struct 的使用
# struct.pack 用于python中的值, 转换为字符串(因为Python中没有字节(Byte)类型，可以把这里的字符串理解为字节流，或字节数组)
# struct.unpack 做的工作刚好与 pack 相反, 函数返回一个元组
import struct

theline = struct.pack("5s 3x 8s 8s 10s", "aaaaa",  "bbbbbbbb", "cccccccc", "++++++++++")
# 5字节字符串, 跳过3字节, 2个8字节字符串, 以及其余所有的:
# x跳过字节自动填充\00
baseformat = "5s 3x 8s 8s"
numremain = len(theline) - struct.calcsize(baseformat)
format = "%s %ds" % (baseformat, numremain)
print repr(theline)
l, s1, s2, t = struct.unpack(format, theline)
# 跳过其余部分
l, s1, s2 = struct.unpack(baseformat, theline[:struct.calcsize(baseformat)])

# 封装成函数
def fields(baseformat, theline, lastfield=False):
    numremain = len(theline) - struct.calcsize(baseformat)
    # lastfield 是否跳过其余部分
    format = "%s %d%s" % (baseformat, numremain, lastfield and "s" or "x")
    return struct.unpack(format, theline)

#  如果 fields 函数经常被调用, 使用元组 (baseformat, theline, lastfield) 作为 key
#  来充分利用 memoizing 机制跳过性能 
def memoizing_fields(baseformat, theline, lastfield=False, _cache = { }):
    key = baseformat, len(theline), lastfield
    format = _cache.get(key)
    if format is None:
        numremain = len(theline) - struct.calcsize(baseformat)
        format = "%s %d%s" % (baseformat, numremain, lastfield and "s" or "x")
        _cache[key] = format    
    return struct.unpack(format, theline)

# 获取5个字节一组的数据
fivers = [ theline[k : k+5] for k in xrange(0, len(theline), 5) ]
print fivers

cuts = [8, 14, 20, 26, 30]
# [0] + cuts = [ 0, 8, 14, 20, 26, 30 ]
# cuts + [None] = [ 8, 14, 20, 26, 30, None ]
pieces = [ theline[i:j] for i, j in zip([0] + cuts, cuts + [None]) ]
print pieces

def split_by(theline, n, lastfield=False):
    pieces = [ theline[k : k+n] for k in xrange(0, len(theline), n) ]
    if not lastfield and len(pieces[-1]) < n:
        pieces.pop()
    return pieces
def split_at(theline, cuts, lastfield=False):
    pieces = [ theline[i:j] for i, j in zip([0] + cuts, cuts + [None]) ]
    if not lastfield:
        pieces.pop()
    return pieces
# 生成器版本
def split_at_yield(theline, cuts, lastfield=False):
    last = 0
    for cut in cuts:
        yield theline[last:cut]
        last = cut
    if lastfield:
        yield theline[last:]
def split_by_yield(theline, n, lastfield=False):
    return split_at_yield(theline, xrange(n, len(theline), n), lastfield)
print split_by("abc", 1, True)
print split_at("abc", [1, 2], True)
for i in split_at_yield("abc", [1, 2], True):
    print i
for i in split_by_yield("abc", 1, True):
    print i

print l
print '-----'
print s1
print '-----'
print s2
print '-----'
print t
print '-----'
