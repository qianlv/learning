#!/usr/bin/python
#encoding=utf-8

import types, tempfile
CHUNK_SIZE = 16 * 1024

def adapt_file(fileObj):
    if isinstance(fileObj, file): return fileObj
    tmpFileObj = tempfile.TemporaryFile()
    while True:
        data = fileObj.read(CHUNK_SIZE)
        if not data:
            break
        tmpFileObj.write(data)
    fileObj.close()
    tmpFileObj.seek(0)
    return tmpFileObj
