#!/usr/bin/python
#encoding=utf-8

astr = "\t1\t  2\t\t3"
# tabs转换为空格, 默认是8个
print astr.expandtabs()
print astr.expandtabs(4)

# 空格转换成tab
def unexpand(astring, tablen=8):
    import re
    pieces = re.split(r'( +)', astring.expandtabs(tablen))
    print pieces
    lensofar = 0
    for i, piece in enumerate(pieces):
        thislen = len(piece)
        lensofar += thislen
        if piece.isspace():
            # tab 相对于一行的开头计算的
            # 例如: 假设tab为4个空格,那么无论是从第0,1,2,3空格按tab键,都是到达第4个位置
            # 摘自百度知道: http://zhidao.baidu.com/link?url=Gd0mPgDaIjq_HYhBsTMH0AHP7vIBB0yAeN3c1TXyJe77bLimf-zKJbNWC-UYoqvSwWp7YwXlsMq0u6yo1NEXc_
            # \t就是tab，指的是制表位，其实可以这么理解——
            # 位空空空位空空空位空空空位空空空位空空空位空空空位空空空
            # 1和5还有9...这些就是制表位，按了tab后自然就会对其到1、5、9这些格子
            # 假设已有2个字符，按一下tab，就移动到了第5个位置上，有3个字符，按一下tab，仍然是移动到第5个位置上...
            # 如果按2下tab，很明显，上面两者都会移动到第9个格子上
            # 但有些SHELL定义的制表符不是4个字符，而是8个...所以就变成这样
            # 位空空空空空空空位空空空空空空空位空空空空空空空
            # 很明显，按一下tab感觉距离“变长了”
            # ——因此，之所以说是制表位，顾名思义就是对对齐方便做成表格
            numblanks = lensofar % tablen
            numtabs = (thislen - numblanks + tablen - 1) / tablen
            pieces[i] = '\t' * numtabs + ' ' * numblanks
    return ''.join(pieces)

# 仅仅处理每行开头的tab 
def expand_at_linestart(P, tablen=8):
    import re
    def exp(mo):
        return mo.group().expandtabs(tablen)
    return ''.join([ re.sub(r'^\s+', exp, s) for s in P.splitlines(True) ] )
if __name__ == '__main__':
    print unexpand(astr, 4)
    lines = """
        \t\tabc\t\tbac
        \t acdd\t
    """
    print repr(expand_at_linestart(lines, 4))
