#!/usr/bin/python
#encoding=utf-8

# 文件很大时, 可能很慢, 甚至失败
count = len(open('thefile.txt', 'rU').readlines())
print count

count = -1
for count, line in enumerate(open('thefile.txt', 'rU')):
    pass
count += 1
print count

# 如果行结束是 '\n' 或含 '\n'
count = 0
thefile = open('thefile.txt', 'rb')
while True:
    buffer = thefile.read(8192 * 1024)
    if not buffer:
        break
    count += buffer.count('\n')
print count
thefile.close()
