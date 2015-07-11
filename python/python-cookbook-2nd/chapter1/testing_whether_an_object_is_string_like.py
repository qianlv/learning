#/usr/bin/python
#encoding=utf-8

# str和unicode类型的共同基类basestring
# 无法判断UserString
def isAString(anobj):
    return isinstance(anobj, basestring)

# python 中常用的鸭子判断法: 如果它走路像鸭子，叫声像鸭子，
# 那么对于应用而言，就可以认为它是鸭子了.
def isStringLike(anobj):
    try:
        anobj.lower() + anobj + ''
    except:
        return False
    else:
        return True

print isAString("abc")
import UserString
buf = UserString.MutableString("a"*30)
print buf
print isAString(buf)
print isStringLike(buf)
