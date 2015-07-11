#!/usr/bin/python
#encoding=utf-8

# 判断字符串是文本还是二进制
# Perl的判定法: 如果字符串中包含空值或超过30%的字符的高位为1(字符值大于126)，
# 或是奇怪的控制码

import string
text_characters = ''.join(map(chr, range(32, 127))) + '\n\r\t\b'
null_trans = string.maketrans("", "")

def istext(s, text_characters = text_characters, threshold = 0.30):
    # 如果包含null值，它不是文本
    if "\0" in s:
        return False
    # ''空字符串为文本
    if not s:
        return True
    t = s.translate(null_trans, text_characters)
    # 不超过 30% 的字符是非文本, s 是字符串
    return len(t) / len(s) <= threshold

def istextfile(filename, blocksize = 512, **kwds):
    return istext(open(filename).read(blocksize), **kwds)

if __name__ == '__main__':
    with open('test', 'w') as f:
        f.write(chr(234))
        f.write(chr(189))
    print istextfile('test', threshold = 0.3)

        
