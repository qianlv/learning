#!/usr/bin/python
#encoding=utf-8

import tarfile, os
def make_tar(folder_to_backup, dest_folder, compression='bz2'):
    # 后缀
    if compression:
        dest_ext = '.' + compression
    else:
        dest_ext = ''
    # 相对路径转换为绝对路径
    arcname = os.path.basename(os.path.abspath(folder_to_backup))
    dest_name = '%s.tar%s' % (arcname, dest_ext)
    # join() 这个函式，可以跨平台的产生正确的档案路径
    dest_path = os.path.join(dest_folder, dest_name)
    # 压缩方式
    if compression:
        dest_cmp = ':' + compression
    else:
        dest_cmp = ''
    out = tarfile.TarFile.open(dest_path, 'w' + dest_cmp)
    out.add(folder_to_backup, arcname)
    out.close()
    return dest_path

if __name__ == '__main__':
    make_tar('.', '/home/qianlv/git', '')
    make_tar('/home/qianlv/git/python-cookbook-2nd', '/home/qianlv/git', '')

