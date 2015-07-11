#!/usr/bin/python
#encoding=utf-8

little = "abcE"
big = little.upper()
print big
little = big.lower()
print little
s = 'one tWo thrEe'
print s.capitalize() # 等于s[:1].upper() + s[1:].lower()
print s.title() # 将每个单词的第一个字母大写， 其余转成小写

# 检查字符串是否已经满足需求的方法isupper, islittle, istitle, 
# 由于没有类似iscapitalize的方法
import string

# 不够严谨的版本, 对于空字符串和不含字母的字符串也返回True
def mistakeIscapitalized(str):
    return str == str.capitalize()

null_trans = string.maketrans('', '')
def containsAny(astr, strset):
    return len(strset) != len(strset.translate(null_trans, astr))

def iscapitalize(str):
    return str == str.capitalize() and containsAny(str, string.letters)

if __name__ == '__main__':
    s = chr(189) + chr(199)
    print mistakeIscapitalized(s)
    print iscapitalize(s)

