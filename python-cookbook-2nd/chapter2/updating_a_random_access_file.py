#!/usr/bin/python
#encoding=utf-8

# 修改含有很多固定长度记录的大二进制文件，并写回文件中。

import struct
string_format = '8l'                         # 格式8个4字节的整数
record_size = struct.calcsize(string_format) # 记录长度
record_number = 6                            # 第几条记录
thefile = open('somebinfile', 'r+b')
thefile.seek(record_size * record_number)
buffer = thefile.read(record_size)
fields = list(struct.unpack(string_format, buffer))
# 修改 fields 值
buffer = strcut.pack(string_format, *fields)
# 或是 thefile.seek(-record_size, 1)
thefile.seek(record_size * record_number)
thefile.write(buffer)
thefile.close()
