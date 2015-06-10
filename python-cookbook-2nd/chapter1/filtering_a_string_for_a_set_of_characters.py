#!/usr/bin/python
#encoding=utf-8

import string
# 生成所有字符的可复用的字符串, 还可以作为翻译表, 指明 '无需翻译'
allchars = string.maketrans('', '') 

# 过滤字符串中不属于指定集合的字符
# 即删除 s 中 不在 keep 集合中的字符
def makefilter(keep):
    # delete 为 keep 的补集
    delete = allchars.translate(allchars, keep)
    def thefilter(s):
        return s.translate(allchars, delete)
    return thefilter

# 返回一个严格按照字母表排序且没有重复的字符串
def canonicform(s):
    return makefilter(s)(allchars)

# unicode 的 makefilter
# str 的 translate 的 table 值只一个长度为256的字符串
# unicode 的 translate只接受table值, table可以是一个 list 或 dict，
# 此时的映射表table键值key必须是unicode的位序值[0, 65535], 值value可以是integer, None or unicode
# table 本质是一个实现__getitem__的对象即可, translate在进行转换时应该就是简单通过[]转换

class Keeper(object):
    def __init__(self, keep):
        self.keep = set(map(ord, keep))
    def __getitem__(self, n):
        if n not in self.keep:
            return None
        return unichr(n)
    def __call__(self, s):
        return unicode(s).translate(self)
makefilter_unicode = Keeper
if __name__ == '__main__':
    digits_only = makefilter(string.digits)
    print digits_only("abc1054059790--00")
    print canonicform("bfaee232")

    just_vowel = makefilter_unicode('aeiouy')
    print just_vowel(u'four socre and seven years ago')
