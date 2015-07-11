#/usr/bin/python
#encoding=utf-8

import string

# 封装translate
# delete 和 keep 尽量不要同时指定
def translator(frm='', to='', delete='', keep=None):
    if len(to) == 1:
        to = to * len(frm)
    table = string.maketrans(frm, to)
    # 当 keep 被指定设置 delete 为除去keep为的所有字符,
    # 如果delete也指定, delete优先
    if keep is not None:
        allchars = string.maketrans('', '')
        delete = allchars.translate(allchars, keep.translate(allchars, delete))
    def translate(s):
        return s.translate(table, delete)
    return translate

test = translator(frm = 'G', to = '1', delete='abc')
print '-------------------------------'
print test('abcabceeeeeffffGGGGGGGGGGGGG')
