#/usr/bin/python
#encoding=utf-8

# 检查seq中是否含有aset中的项
def containsAny(seq, aset):
    for c in seq:
        if c in aset: return True
    return False

# 检查seq中是否只含有aset中的项
def containsOnly(seq, aset):
    for c in seq:
        if c not in aset: return False
    return True
# 检查seq中是否含有aset中的所有项    
def containsAll(seq, aset):
    # set(a).difference(b), 返回a中所有不属于b的元素
    return not set(aset).difference(seq)

print containsAny([1, 2, 3, 4], [3, 4, 5])
print containsAny([1, 2, 3, 4], [5, 6])
print '---------------'
print containsOnly([1, 2, 3, 3], [1, 2, 3, 4])
print containsOnly([1, 2, 3, 3], [1, 2])
print '---------------'
print containsAll([1, 2, 3, 3], [1, 2, 3])
print containsAll([1, 2, 3, 3], [1, 2, 3, 4])

# 如果seq, aset是字符串可能不需要上述通用的方法,
# 基于translate的特殊方法
import string
table = string.maketrans('','') #不进行转换
def containsAnyStr(astr, strset):
    # strset.translate(table, astr) 返回删除astr中字符后的strset，即返回一个strset的一个子序列
    # 如果长度相等说明strset没有删除任何字符，因此astr中不含有strset中的字符
    return len(strset) != len(strset.translate(table, astr))
def containsAllStr(astr, strset):
    return not strset.translate(table, astr)
