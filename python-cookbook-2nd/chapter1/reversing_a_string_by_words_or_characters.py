#/usr/bin/python
#encoding=utf-8

# 按字符反转
astring = "word abase abandom"
revstring = astring[::-1]
print revstring

# 按单词反转
revwords = astring.split()
revwords.reverse()
revwords = ' '.join(revwords)
print revwords

revwords2 = ' '.join(astring.split()[::-1])
print revwords2

# 保持原有空格
astring = "word    abase  abandom"
import re
# 通过正则表达式将字符串分离。如果用括号将正则表达式括起来,
# 那么匹配的字符串也会被列入到list中返回.
revwords = re.split(r'(\s+)', astring)
revwords.reverse()
revwords = ''.join(revwords)
print revwords

revwords2 = ''.join(re.split(r'(\s+)', astring)[::-1])
print revwords2

# 用reversed代替[::-1]
print ''.join(reversed(re.split(r'(\s+)', astring)))

