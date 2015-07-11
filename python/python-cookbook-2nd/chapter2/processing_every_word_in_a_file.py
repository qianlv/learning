#!/usr/bin/python
#encoding=utf-8

# 以空格分割的
for line in open('thefile.txt', 'rU'):
    for word in line.split():
        print word
print '-------------------'

# 词的定义改变
import re
re_word = re.compile(r"[\w'-]+")
for line in open('thefile.txt', 'rU'):
    for word in re_word.finditer(line):
        print word.group()

# 封装成迭代器
def word_of_file(thefilepath, line_to_words = str.split):
    the_file = open(thefilepath, 'rU')
    for line in the_file:
        for word in line_to_words(line):
            yield word
    the_file.close()
# 在进行封装，对于单词定义的改变
def word_of_re(thefilepath, repattern=r"[\w'-]+"):
    wre = re.compile(repattern)
    def line_to_words(line):
        for mo in wre.finditer(line):
            yield mo.group(0)
    return word_of_file(thefilepath, line_to_words)

if __name__ == '__main__':
    print '-------------------'
    for word in word_of_file('thefile.txt'):
        print word
    print '-------------------'
    for word in word_of_re('thefile.txt'):
        print word
