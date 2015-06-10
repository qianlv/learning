#!/usr/bin/python
#encoding=utf-8

import re

# 把字符串所有能够在指定的字典中找到的子串都被替换为字典中对应的值
def multiple_replace(text, adict):
    # 对字典使用map时, 传递的值为字典的key
    # re.escape(string) 将string中的正则表达式元字符如*/+/?等之前加上转义符再返回, 
    # 即字符串的原意
    # rx 结果为形如'key1|key2|key3|...|keyN'
    rx = re.compile('|'.join(map(re.escape, adict)))
    def one_xlat(match):
        return adict[match.group(0)]
    return rx.sub(one_xlat, text)

# 闭包版
def make_xlat(*args):
    adict = dict(*args)
    rx = re.compile('|'.join(map(re.escape, adict)))
    def one_xlat(match):
        return adict[match.group(0)]
    def xlat(text):
        return rx.sub(one_xlat, text)
    return xlat

# 替换单词版本
# 修改rx 为 re.compile(r'\b%s\b' % '\b|\b'.join(map(re.escape, adcit)))
def make_xlat_word(*args):
    adict = dict(*args)
    rx = re.compile(r'\b%s\b' % r'\b|\b'.join(map(re.escape, adict)))
    def one_xlat(match):
        return adict[match.group(0)]
    def xlat(text):
        return rx.sub(one_xlat, text)
    return xlat

# 使用类实现, 通过继承修改正则的模式
class make_xlat_class:
    def __init__(self, *args, **kwds):
        self.adict = dict(*args, **kwds)
        self.rx = self.make_rx()
    def make_rx(self):
        return re.compile('|'.join(map(re.escape, self.adict)))
    def one_xlat(self, match):
        return self.adict[match.group(0)]
    def __call__(self, text):
        return self.rx.sub(self.one_xlat, text)

# \b 匹配一个单词边界，也就是单词和空格之间的位置，不匹配任何字符
# 举例3：表达式 ".\b." 在匹配 "@@@abc" 时，匹配结果是：成功；匹配到的内容是："@a"；匹配到的位置是：开始于2，结束于4。
# 进一步说明："\b" 与 "^" 和 "$" 类似，本身不匹配任何字符，但是它要求它在匹配结果中所处位置的左右两边，其中一边是 "\w" 范围，另一边是 非"\w" 的范围。
# 举例4：表达式 "\bend\b" 在匹配 "weekend,endfor,end" 时，匹配结果是：成功；匹配到的内容是："end"；匹配到的位置是：开始于15，结束于18。
# 参考: http://www.regexlab.com/start/

class make_xlat_class_word_by_word(make_xlat_class):
    def make_rx(self):
        return re.compile(r'\b%s\b' % r'\b|\b'.join(map(re.escape, self.adict)))

if __name__ == '__main__':
    text = "Larry Wall is the creator of Perltest"
    adict = {
        "Larry Wall" : "Guido van Rossum",
        "creator" : "Benevolent Dictator for Life",
        "Perl" : "Python",
    }
    print multiple_replace(text, adict)
    translate = make_xlat(adict)
    print translate(text)
    translate_word = make_xlat_word(adict)
    print translate_word(text)
    translate_class = make_xlat_class(adict)
    print translate_class(text)
    translate_class_word = make_xlat_class_word_by_word(adict)
    print translate_class_word(text)
